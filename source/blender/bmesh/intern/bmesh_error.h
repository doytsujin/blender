/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#pragma once

/** \file
 * \ingroup bmesh
 */

#include "bmesh_operator_api.h"

/*----------- bmop error system ----------*/

/* pushes an error onto the bmesh error stack.
 * if msg is null, then the default message for the errorcode is used.*/
void BMO_error_raise(BMesh *bm, BMOperator *owner, int errcode, const char *msg);

/* gets the topmost error from the stack.
 * returns error code or 0 if no error.*/
int BMO_error_get(BMesh *bm, const char **msg, BMOperator **op);
bool BMO_error_occurred(BMesh *bm);

/* same as geterror, only pops the error off the stack as well */
int BMO_error_pop(BMesh *bm, const char **msg, BMOperator **op);
void BMO_error_clear(BMesh *bm);

/* this is meant for handling errors, like self-intersection test failures.
 * it's dangerous to handle errors in general though, so disabled for now. */

/* catches an error raised by the op pointed to by catchop.
 * errorcode is either the errorcode, or BMERR_ALL for any
 * error.*/

/* not yet implemented.
 * int BMO_error_catch_op(BMesh *bm, BMOperator *catchop, int errorcode, char **msg);
 */

/*------ error code defines -------*/

/*error messages*/
enum {
  BMERR_CONNECTVERT_FAILED = 1,
  BMERR_DISSOLVEFACES_FAILED,
  BMERR_INVALID_SELECTION,
  BMERR_MESH_ERROR,
  BMERR_CONVEX_HULL_FAILED,

  BMERR_TOTAL,
};

/* BMESH_ASSERT */
#ifdef WITH_ASSERT_ABORT
#  define _BMESH_DUMMY_ABORT abort
#else
#  define _BMESH_DUMMY_ABORT() (void)0
#endif

/* this is meant to be higher level then BLI_assert(),
 * its enabled even when in Release mode*/
#define BMESH_ASSERT(a) \
  (void)((!(a)) ? ((fprintf(stderr, \
                            "BMESH_ASSERT failed: %s, %s(), %d at \'%s\'\n", \
                            __FILE__, \
                            __func__, \
                            __LINE__, \
                            STRINGIFY(a)), \
                    _BMESH_DUMMY_ABORT(), \
                    NULL)) : \
                  NULL)
