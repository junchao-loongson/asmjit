// This file is part of AsmJit project <https://asmjit.com>
//
// See asmjit.h or LICENSE.md for license and copyright information
// SPDX-License-Identifier: Zlib

#ifndef ASMJIT_LA_A64ARCHTRAITS_P_H_INCLUDED
#define ASMJIT_LA_A64ARCHTRAITS_P_H_INCLUDED

#include "../core/archtraits.h"
#include "../core/misc_p.h"
#include "../core/type.h"
#include "../loongarch/la64globals.h"
#include "../loongarch/la64operand.h"

ASMJIT_BEGIN_SUB_NAMESPACE(la64)

//! \cond INTERNAL
//! \addtogroup asmjit_a64
//! \{

static const constexpr ArchTraits la64ArchTraits = {
  // SP/FP/LR/PC.
  Gp::kIdSp, Gp::kIdFp, Gp::kIdLr, 0xFF,

  // Reserved.
  { 0, 0, 0 },

  // HW stack alignment (Loongarch requires stack aligned to 16 bytes at HW level).
  16,

  // Min/max stack offset - byte addressing is the worst, VecQ addressing the best.
  4095, 65520,

  // Instruction hints [Gp, Vec, ExtraVirt2, ExtraVirt3].
  {{
    InstHints::kPushPop,
    InstHints::kPushPop,
    InstHints::kNoHints,
    InstHints::kNoHints
  }},

  // RegInfo.
  #define V(index) OperandSignature{RegTraits<RegType(index)>::kSignature}
  {{ ASMJIT_LOOKUP_TABLE_32(V, 0) }},
  #undef V

  // RegTypeToTypeId.
  #define V(index) TypeId(RegTraits<RegType(index)>::kTypeId)
  {{ ASMJIT_LOOKUP_TABLE_32(V, 0) }},
  #undef V

  // TypeIdToRegType.
  #define V(index) (index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kInt8)    ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kUInt8)   ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kInt16)   ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kUInt16)  ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kInt32)   ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kUInt32)  ? RegType::kLA_GpW   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kInt64)   ? RegType::kLA_GpX   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kUInt64)  ? RegType::kLA_GpX   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kIntPtr)  ? RegType::kLA_GpX   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kUIntPtr) ? RegType::kLA_GpX   : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kFloat32) ? RegType::kLA_VecS  : \
                    index + uint32_t(TypeId::_kBaseStart) == uint32_t(TypeId::kFloat64) ? RegType::kLA_VecD  : RegType::kNone)
  {{ ASMJIT_LOOKUP_TABLE_32(V, 0) }},
  #undef V

  // Word names of 8-bit, 16-bit, 32-bit, and 64-bit quantities.
  {
    ArchTypeNameId::kByte,
    ArchTypeNameId::kHWord,
    ArchTypeNameId::kWord,
    ArchTypeNameId::kXWord
  }
};

//! \}
//! \endcond

ASMJIT_END_SUB_NAMESPACE

#endif // ASMJIT_LA_A64ARCHTRAITS_P_H_INCLUDED
