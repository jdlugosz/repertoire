// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined DLUGOSZ_CLASSICS_POINTERS_DEFINED
#define DLUGOSZ_CLASSICS_POINTERS_DEFINED

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "classics\pointers=infrastructure.h"
#include "classics\pointers=const_handle.h"
#include "classics\pointers=const_baro.h"
#include "classics\pointers=baro.h"
#include "classics\pointers=handle.h"
#include "classics\pointers=cow.h"
#include "classics\pointers=can_handle.h"
#include "classics\pointers=casts.h"

// >> will add COM stuff

#endif

