// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gt_enum.proto

#ifndef PROTOBUF_gt_5fenum_2eproto__INCLUDED
#define PROTOBUF_gt_5fenum_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace gt_msg {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_gt_5fenum_2eproto();
void protobuf_AssignDesc_gt_5fenum_2eproto();
void protobuf_ShutdownFile_gt_5fenum_2eproto();


enum Object_Type_Enum {
  SceneObj = 0,
  PlayerObject = 1,
  NpcObject = 2,
  Boss = 3,
  Object_Type_Enum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Object_Type_Enum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Object_Type_Enum_IsValid(int value);
const Object_Type_Enum Object_Type_Enum_MIN = SceneObj;
const Object_Type_Enum Object_Type_Enum_MAX = Boss;
const int Object_Type_Enum_ARRAYSIZE = Object_Type_Enum_MAX + 1;

const ::google::protobuf::EnumDescriptor* Object_Type_Enum_descriptor();
inline const ::std::string& Object_Type_Enum_Name(Object_Type_Enum value) {
  return ::google::protobuf::internal::NameOfEnum(
    Object_Type_Enum_descriptor(), value);
}
inline bool Object_Type_Enum_Parse(
    const ::std::string& name, Object_Type_Enum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Object_Type_Enum>(
    Object_Type_Enum_descriptor(), name, value);
}
enum JobType {
  None = 0,
  JobTanke = 1,
  JobZhanShi = 2,
  JobCiKe = 3,
  JobFaShi = 4,
  JobSheShou = 5,
  JobFuZu = 6,
  JobMax = 7,
  JobType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  JobType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool JobType_IsValid(int value);
const JobType JobType_MIN = None;
const JobType JobType_MAX = JobMax;
const int JobType_ARRAYSIZE = JobType_MAX + 1;

const ::google::protobuf::EnumDescriptor* JobType_descriptor();
inline const ::std::string& JobType_Name(JobType value) {
  return ::google::protobuf::internal::NameOfEnum(
    JobType_descriptor(), value);
}
inline bool JobType_Parse(
    const ::std::string& name, JobType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<JobType>(
    JobType_descriptor(), name, value);
}
enum SkillEffect_Type {
  EffectNone = 0,
  EffectRush = 1,
  Bullet = 2,
  Scope = 3,
  Rotation = 4,
  SkillEffect_Type_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  SkillEffect_Type_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool SkillEffect_Type_IsValid(int value);
const SkillEffect_Type SkillEffect_Type_MIN = EffectNone;
const SkillEffect_Type SkillEffect_Type_MAX = Rotation;
const int SkillEffect_Type_ARRAYSIZE = SkillEffect_Type_MAX + 1;

const ::google::protobuf::EnumDescriptor* SkillEffect_Type_descriptor();
inline const ::std::string& SkillEffect_Type_Name(SkillEffect_Type value) {
  return ::google::protobuf::internal::NameOfEnum(
    SkillEffect_Type_descriptor(), value);
}
inline bool SkillEffect_Type_Parse(
    const ::std::string& name, SkillEffect_Type* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SkillEffect_Type>(
    SkillEffect_Type_descriptor(), name, value);
}
enum DamageType {
  DamageNone = 0,
  PhysicsDepartment = 1,
  MagicDepartment = 2,
  CureDepartment = 3,
  DamageType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  DamageType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool DamageType_IsValid(int value);
const DamageType DamageType_MIN = DamageNone;
const DamageType DamageType_MAX = CureDepartment;
const int DamageType_ARRAYSIZE = DamageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* DamageType_descriptor();
inline const ::std::string& DamageType_Name(DamageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    DamageType_descriptor(), value);
}
inline bool DamageType_Parse(
    const ::std::string& name, DamageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DamageType>(
    DamageType_descriptor(), name, value);
}
enum RangeType {
  CureOne = 0,
  Monomer = 1,
  AimCircle = 2,
  SelfCircle = 3,
  BeeLine = 4,
  Sector = 5,
  RangeType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  RangeType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool RangeType_IsValid(int value);
const RangeType RangeType_MIN = CureOne;
const RangeType RangeType_MAX = Sector;
const int RangeType_ARRAYSIZE = RangeType_MAX + 1;

const ::google::protobuf::EnumDescriptor* RangeType_descriptor();
inline const ::std::string& RangeType_Name(RangeType value) {
  return ::google::protobuf::internal::NameOfEnum(
    RangeType_descriptor(), value);
}
inline bool RangeType_Parse(
    const ::std::string& name, RangeType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<RangeType>(
    RangeType_descriptor(), name, value);
}
enum SkillType {
  Initiative = 0,
  Passiveness = 1,
  AutoTrigger = 2,
  SkillType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  SkillType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool SkillType_IsValid(int value);
const SkillType SkillType_MIN = Initiative;
const SkillType SkillType_MAX = AutoTrigger;
const int SkillType_ARRAYSIZE = SkillType_MAX + 1;

const ::google::protobuf::EnumDescriptor* SkillType_descriptor();
inline const ::std::string& SkillType_Name(SkillType value) {
  return ::google::protobuf::internal::NameOfEnum(
    SkillType_descriptor(), value);
}
inline bool SkillType_Parse(
    const ::std::string& name, SkillType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SkillType>(
    SkillType_descriptor(), name, value);
}
enum Skill_DamageType {
  SkillDamageNone = 0,
  SkillDamageHit = 1,
  SkillDamageMiss = 2,
  Skill_DamageType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Skill_DamageType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Skill_DamageType_IsValid(int value);
const Skill_DamageType Skill_DamageType_MIN = SkillDamageNone;
const Skill_DamageType Skill_DamageType_MAX = SkillDamageMiss;
const int Skill_DamageType_ARRAYSIZE = Skill_DamageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Skill_DamageType_descriptor();
inline const ::std::string& Skill_DamageType_Name(Skill_DamageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Skill_DamageType_descriptor(), value);
}
inline bool Skill_DamageType_Parse(
    const ::std::string& name, Skill_DamageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Skill_DamageType>(
    Skill_DamageType_descriptor(), name, value);
}
enum TargetType {
  enemy = 0,
  self = 1,
  TargetType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  TargetType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool TargetType_IsValid(int value);
const TargetType TargetType_MIN = enemy;
const TargetType TargetType_MAX = self;
const int TargetType_ARRAYSIZE = TargetType_MAX + 1;

const ::google::protobuf::EnumDescriptor* TargetType_descriptor();
inline const ::std::string& TargetType_Name(TargetType value) {
  return ::google::protobuf::internal::NameOfEnum(
    TargetType_descriptor(), value);
}
inline bool TargetType_Parse(
    const ::std::string& name, TargetType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TargetType>(
    TargetType_descriptor(), name, value);
}
enum AddonIndexEnum {
  AddonNone = 0,
  AddonFoot_R = 1,
  AddonFoot_L = 2,
  AddonHead = 3,
  AddonSpine = 4,
  AddonHandR = 5,
  AddonHandL = 6,
  AddonMax = 7,
  AddonIndexEnum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  AddonIndexEnum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool AddonIndexEnum_IsValid(int value);
const AddonIndexEnum AddonIndexEnum_MIN = AddonNone;
const AddonIndexEnum AddonIndexEnum_MAX = AddonMax;
const int AddonIndexEnum_ARRAYSIZE = AddonIndexEnum_MAX + 1;

const ::google::protobuf::EnumDescriptor* AddonIndexEnum_descriptor();
inline const ::std::string& AddonIndexEnum_Name(AddonIndexEnum value) {
  return ::google::protobuf::internal::NameOfEnum(
    AddonIndexEnum_descriptor(), value);
}
inline bool AddonIndexEnum_Parse(
    const ::std::string& name, AddonIndexEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AddonIndexEnum>(
    AddonIndexEnum_descriptor(), name, value);
}
enum AnimationType {
  AnimationNone = 0,
  Idel = 1,
  Run = 2,
  Death = 3,
  Spell1 = 4,
  Spell2 = 5,
  Spell3 = 6,
  Ack1 = 7,
  Ack2 = 8,
  Ack3 = 9,
  Ack4 = 10,
  Dodge = 11,
  Beaten = 12,
  Ready = 13,
  Rush = 14,
  Swoon = 15,
  Stun = 16,
  Born = 17,
  SpellRun = 18,
  Succeed = 19,
  Fail = 20,
  Max = 21,
  AnimationType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  AnimationType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool AnimationType_IsValid(int value);
const AnimationType AnimationType_MIN = AnimationNone;
const AnimationType AnimationType_MAX = Max;
const int AnimationType_ARRAYSIZE = AnimationType_MAX + 1;

const ::google::protobuf::EnumDescriptor* AnimationType_descriptor();
inline const ::std::string& AnimationType_Name(AnimationType value) {
  return ::google::protobuf::internal::NameOfEnum(
    AnimationType_descriptor(), value);
}
inline bool AnimationType_Parse(
    const ::std::string& name, AnimationType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AnimationType>(
    AnimationType_descriptor(), name, value);
}
enum BenefitType {
  Increase = 0,
  Decrease = 1,
  BenefitType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  BenefitType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool BenefitType_IsValid(int value);
const BenefitType BenefitType_MIN = Increase;
const BenefitType BenefitType_MAX = Decrease;
const int BenefitType_ARRAYSIZE = BenefitType_MAX + 1;

const ::google::protobuf::EnumDescriptor* BenefitType_descriptor();
inline const ::std::string& BenefitType_Name(BenefitType value) {
  return ::google::protobuf::internal::NameOfEnum(
    BenefitType_descriptor(), value);
}
inline bool BenefitType_Parse(
    const ::std::string& name, BenefitType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BenefitType>(
    BenefitType_descriptor(), name, value);
}
enum ReplaceType {
  ReplaceNone = 0,
  Pileup = 1,
  Replace = 2,
  pileup_time = 3,
  ReplaceType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ReplaceType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ReplaceType_IsValid(int value);
const ReplaceType ReplaceType_MIN = ReplaceNone;
const ReplaceType ReplaceType_MAX = pileup_time;
const int ReplaceType_ARRAYSIZE = ReplaceType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ReplaceType_descriptor();
inline const ::std::string& ReplaceType_Name(ReplaceType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ReplaceType_descriptor(), value);
}
inline bool ReplaceType_Parse(
    const ::std::string& name, ReplaceType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ReplaceType>(
    ReplaceType_descriptor(), name, value);
}
enum InfluenceType {
  Self = 0,
  Enemy = 1,
  InfluenceType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  InfluenceType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool InfluenceType_IsValid(int value);
const InfluenceType InfluenceType_MIN = Self;
const InfluenceType InfluenceType_MAX = Enemy;
const int InfluenceType_ARRAYSIZE = InfluenceType_MAX + 1;

const ::google::protobuf::EnumDescriptor* InfluenceType_descriptor();
inline const ::std::string& InfluenceType_Name(InfluenceType value) {
  return ::google::protobuf::internal::NameOfEnum(
    InfluenceType_descriptor(), value);
}
inline bool InfluenceType_Parse(
    const ::std::string& name, InfluenceType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<InfluenceType>(
    InfluenceType_descriptor(), name, value);
}
enum ObjectBaseAtribute {
  AtributeNone = 0,
  PhysicAtk = 1,
  MagicAtk = 2,
  Hp = 3,
  Defance = 4,
  MagicDef = 5,
  BurstsRate = 6,
  FlashRate = 7,
  HitRate = 8,
  ObjectBaseAtribute_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ObjectBaseAtribute_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ObjectBaseAtribute_IsValid(int value);
const ObjectBaseAtribute ObjectBaseAtribute_MIN = AtributeNone;
const ObjectBaseAtribute ObjectBaseAtribute_MAX = HitRate;
const int ObjectBaseAtribute_ARRAYSIZE = ObjectBaseAtribute_MAX + 1;

const ::google::protobuf::EnumDescriptor* ObjectBaseAtribute_descriptor();
inline const ::std::string& ObjectBaseAtribute_Name(ObjectBaseAtribute value) {
  return ::google::protobuf::internal::NameOfEnum(
    ObjectBaseAtribute_descriptor(), value);
}
inline bool ObjectBaseAtribute_Parse(
    const ::std::string& name, ObjectBaseAtribute* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ObjectBaseAtribute>(
    ObjectBaseAtribute_descriptor(), name, value);
}
enum AnimationEvent_Enum {
  AniDead = 0,
  AniFight = 1,
  AniIdle = 2,
  AnimationEvent_Enum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  AnimationEvent_Enum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool AnimationEvent_Enum_IsValid(int value);
const AnimationEvent_Enum AnimationEvent_Enum_MIN = AniDead;
const AnimationEvent_Enum AnimationEvent_Enum_MAX = AniIdle;
const int AnimationEvent_Enum_ARRAYSIZE = AnimationEvent_Enum_MAX + 1;

const ::google::protobuf::EnumDescriptor* AnimationEvent_Enum_descriptor();
inline const ::std::string& AnimationEvent_Enum_Name(AnimationEvent_Enum value) {
  return ::google::protobuf::internal::NameOfEnum(
    AnimationEvent_Enum_descriptor(), value);
}
inline bool AnimationEvent_Enum_Parse(
    const ::std::string& name, AnimationEvent_Enum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AnimationEvent_Enum>(
    AnimationEvent_Enum_descriptor(), name, value);
}
enum BuffEffectType {
  BufEffectNone = 0,
  AttributeAdded = 1,
  AttributePercent = 2,
  Invincibility = 3,
  Icebound = 4,
  Qualm = 5,
  Slowdown = 6,
  SlowUp = 7,
  SuckBlood = 8,
  BuffEffectType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  BuffEffectType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool BuffEffectType_IsValid(int value);
const BuffEffectType BuffEffectType_MIN = BufEffectNone;
const BuffEffectType BuffEffectType_MAX = SuckBlood;
const int BuffEffectType_ARRAYSIZE = BuffEffectType_MAX + 1;

const ::google::protobuf::EnumDescriptor* BuffEffectType_descriptor();
inline const ::std::string& BuffEffectType_Name(BuffEffectType value) {
  return ::google::protobuf::internal::NameOfEnum(
    BuffEffectType_descriptor(), value);
}
inline bool BuffEffectType_Parse(
    const ::std::string& name, BuffEffectType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<BuffEffectType>(
    BuffEffectType_descriptor(), name, value);
}
enum ObjectEnemySide {
  NeturalObj = 0,
  MySelfObj = 1,
  EnemyObj = 2,
  ObjectEnemySide_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ObjectEnemySide_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ObjectEnemySide_IsValid(int value);
const ObjectEnemySide ObjectEnemySide_MIN = NeturalObj;
const ObjectEnemySide ObjectEnemySide_MAX = EnemyObj;
const int ObjectEnemySide_ARRAYSIZE = ObjectEnemySide_MAX + 1;

const ::google::protobuf::EnumDescriptor* ObjectEnemySide_descriptor();
inline const ::std::string& ObjectEnemySide_Name(ObjectEnemySide value) {
  return ::google::protobuf::internal::NameOfEnum(
    ObjectEnemySide_descriptor(), value);
}
inline bool ObjectEnemySide_Parse(
    const ::std::string& name, ObjectEnemySide* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ObjectEnemySide>(
    ObjectEnemySide_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace gt_msg

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::gt_msg::Object_Type_Enum> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::Object_Type_Enum>() {
  return ::gt_msg::Object_Type_Enum_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::JobType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::JobType>() {
  return ::gt_msg::JobType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::SkillEffect_Type> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::SkillEffect_Type>() {
  return ::gt_msg::SkillEffect_Type_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::DamageType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::DamageType>() {
  return ::gt_msg::DamageType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::RangeType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::RangeType>() {
  return ::gt_msg::RangeType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::SkillType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::SkillType>() {
  return ::gt_msg::SkillType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::Skill_DamageType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::Skill_DamageType>() {
  return ::gt_msg::Skill_DamageType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::TargetType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::TargetType>() {
  return ::gt_msg::TargetType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::AddonIndexEnum> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::AddonIndexEnum>() {
  return ::gt_msg::AddonIndexEnum_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::AnimationType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::AnimationType>() {
  return ::gt_msg::AnimationType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::BenefitType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::BenefitType>() {
  return ::gt_msg::BenefitType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::ReplaceType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::ReplaceType>() {
  return ::gt_msg::ReplaceType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::InfluenceType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::InfluenceType>() {
  return ::gt_msg::InfluenceType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::ObjectBaseAtribute> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::ObjectBaseAtribute>() {
  return ::gt_msg::ObjectBaseAtribute_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::AnimationEvent_Enum> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::AnimationEvent_Enum>() {
  return ::gt_msg::AnimationEvent_Enum_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::BuffEffectType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::BuffEffectType>() {
  return ::gt_msg::BuffEffectType_descriptor();
}
template <> struct is_proto_enum< ::gt_msg::ObjectEnemySide> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gt_msg::ObjectEnemySide>() {
  return ::gt_msg::ObjectEnemySide_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_gt_5fenum_2eproto__INCLUDED
