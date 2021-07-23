#include "reflected_class.h"
#include "functiongenerator.h"
#include "fieldgenerator.h"

namespace re_reflect {
void ReflectedClass::Generate(ASTContext *ctx, raw_ostream &os) {
  SmallString<64> str;
  SmallString<64> type;
  raw_svector_ostream stos(type);
  record->printQualifiedName(stos);

  /* File header: */
  os << "/* this file is auto-generated. do not edit! */\n";
  os << "#pragma once\n";
  os << "#include \"metareflect.hxx\"\n";
  os << "namespace metareflect\n{\n\n";

  SmallVector<PropertyAnnotations, 8> propertyAnnotations;
  SmallVector<FunctionAnnotations, 8> functionAnnotations;

  /* Verify CLASS annotation. */
  for (auto &attr : record->attrs()) {
    if (attr->getKind() == attr::Annotate) {
      auto ref = GetAnnotations(attr, str);
      assert(ref.startswith("reflect-class") && "incorrect annotation");
    }
  }

  /* Generate PROPERTY annotations. */
  for (auto &field : fields) {
    Attr *attr = GetAnnotateAttr(field);
    assert(attr != nullptr);
    propertyAnnotations.push_back(
        GenerateFieldAttributes(GetAnnotations(attr, str)));
  }

  /* Generate FUNCTION annotations. */
  for (auto &func : functions) {
    Attr *attr = GetAnnotateAttr(func);
    assert(attr != nullptr);
    functionAnnotations.push_back(
        GenerateFunctionAttributes(GetAnnotations(attr, str)));
  }

  /* Mark class as serializable if one or more fields are serialized. */
  ClassAnnotations classFlags;
  classFlags.isSerializable =
      std::any_of(propertyAnnotations.begin(), propertyAnnotations.end(),
                  [](PropertyAnnotations &v) { return v.serialized; });
  classFlags.hasBeforeSerialize = HasFunctionOfName("BeforeSerialize");
  classFlags.hasAfterSerialize = HasFunctionOfName("AfterSerialize");
  classFlags.hasCustomSerialize = HasFunctionOfName("Serialize");
  classFlags.hasCustomDump = HasFunctionOfName("Dump");
  os << "template<> struct IsSerializable<" << type
     << "> { static constexpr bool value = "
     << (classFlags.isSerializable ? "true" : "false") << "; };\n";

  os << "template<> struct HasBeforeSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasBeforeSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasAfterSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasAfterSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasCustomSerialize<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasCustomSerialize ? "true" : "false") << "; };\n";

  os << "template<> struct HasCustomDump<" << type
     << "> { static constexpr bool value = "
     << (classFlags.hasCustomDump ? "true" : "false") << "; };\n";

  os << "namespace detail\n{\n";

  /* GetClass function */
  /* os << "template<> struct ClassResolver<" << type << ">;\n"; */
  os << "template<>\n"
     << "Class const *\n"
     /* << "ClassResolver<" << type << ">::Get() noexcept\n" */
     /* << "GetClass<" << type << ">() noexcept\n" */
     << "GetClassImpl(ClassTag<" << type << ">) noexcept\n"
     << "{\n"
     << "static detail::ClassStorage<" << type << ", " << fields.size()
     << ", " << functions.size() << ">"
     << " reflected([](auto self) {\n";

  /* Fields */
  FieldGenerator fieldGenerator(ctx, type, "self->fields");
  for (unsigned i = 0, n = fields.size(); i < n; ++i)
    fieldGenerator.Generate(i, fields[i], propertyAnnotations[i], os);

  /* Functions */
  FunctionGenerator funcGenerator(ctx, type, "self->functions");
  for (unsigned i = 0, n = functions.size(); i < n; ++i)
    funcGenerator.Generate(i, functions[i], functionAnnotations[i], os);

  os << "});\n"
     << "static Class cache(\n"
     << "sizeof(" << type << "),\n"
     << "Hash(\"" << type << "\"),\n"
     << "nullptr/*TODO: baseclass*/,\n"
     << "reflected.fields,\n"
     << "reflected.fields + reflected.numFields,\n"
     << "reflected.functions,\n"
     << "reflected.functions + reflected.numFunctions,\n"
     << "\"" << type << "\",\n"
     << classFlags.Flags() << ");\n"
     << "return &cache;\n";
  os << "}\n\n";

  /* GetType function */
  /* os << "template<> struct TypeResolver<" << type << ">;\n"; */
  os << "template<>\n"
     << "Type const *\n"
     /* << "TypeResolver<" << type << ">::Get() noexcept\n" */
     /* << "GetType<" << type << ">() noexcept\n" */
     << "GetTypeImpl(TypeTag<" << type << ">) noexcept\n"
     << "{\n"
     /* << "return ClassResolver<" << type << ">::Get();\n" */
     << "return GetClass<" << type << ">();\n"
     << "}\n";

  os << "} /* namespace detail */\n";
  os << "} /* namespace metareflect */\n\n";
}

void ReflectedClass::AddField(FieldDecl const *field) {
  fields.push_back(field);
}

void ReflectedClass::AddFunction(FunctionDecl const *function) {
  functions.push_back(function);
}

/* ========================================================================= */
/* Generator                                                                 */
/* ========================================================================= */
PropertyAnnotations
ReflectedClass::GenerateFieldAttributes(StringRef const &attr) {
  assert(attr.startswith("reflect-property") && "incorrect annotation");
  auto pair = attr.split(";");

  PropertyAnnotations ret;
  auto setAttributes = [&ret](StringRef const &s) -> bool {
    if (s.equals_lower("serialized")) {
      return (ret.serialized = true);

    } else if (s.startswith_lower("width")) {
      size_t idx = s.find_first_of('=');
      auto sref = s.substr(idx + 1);
      unsigned width;
      sref.getAsInteger(10, width);
      ret.width = width;
      return true;

    } else if (s.equals_lower("cstring")) {
      return (ret.isCString = true);
    }

    return false;
  };

  ForEachProperty(pair.second, setAttributes);
  return ret;
}

FunctionAnnotations
ReflectedClass::GenerateFunctionAttributes(StringRef const &attr) {
  assert(attr.startswith("reflect-function") && "incorrect annotation");
  auto pair = attr.split(";");

  FunctionAnnotations ret;
  auto setAttributes = [&ret](StringRef const &s) -> bool {
    if (s.equals_lower("replicated")) {
      return (ret.replicated = true);
    }

    return false;
  };

  ForEachProperty(pair.second, setAttributes);
  return ret;
}



}
