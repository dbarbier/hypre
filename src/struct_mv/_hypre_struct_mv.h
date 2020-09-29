
#ifndef hypre_STRUCT_MV_HEADER
#define hypre_STRUCT_MV_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "HYPRE_struct_mv.h"
#include "_hypre_utilities.h"

#ifdef __cplusplus
extern "C" {
#endif

/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for the Box structures
 *
 *****************************************************************************/

#ifndef hypre_BOX_HEADER
#define hypre_BOX_HEADER

#ifndef HYPRE_MAXDIM
#define HYPRE_MAXDIM 3
#endif

/*--------------------------------------------------------------------------
 * hypre_Index:
 *
 * This is used to define indices in index space, or dimension sizes of boxes.
 * The hypre_IndexD macro is used to access integer values in each dimension,
 * but it is okay to use standard array syntax, i.e., index[i].
 *--------------------------------------------------------------------------*/

typedef HYPRE_Int  hypre_Index[HYPRE_MAXDIM];
typedef HYPRE_Int *hypre_IndexRef;

/*--------------------------------------------------------------------------
 * hypre_Box:
 *--------------------------------------------------------------------------*/

typedef struct hypre_Box_struct
{
   hypre_Index imin;           /* min bounding indices */
   hypre_Index imax;           /* max bounding indices */
   HYPRE_Int   ndim;           /* number of dimensions */
} hypre_Box;

/*--------------------------------------------------------------------------
 * hypre_BoxArray:
 *   An array of boxes.
 *   Since size can be zero, need to store ndim separately.
 *--------------------------------------------------------------------------*/

typedef struct hypre_BoxArray_struct
{
   hypre_Box  *boxes;         /* Array of boxes */
   HYPRE_Int   size;          /* Size of box array */
   HYPRE_Int   alloc_size;    /* Size of currently alloced space */
   HYPRE_Int   ndim;          /* number of dimensions */
} hypre_BoxArray;

#define hypre_BoxArrayExcess 10

/*--------------------------------------------------------------------------
 * hypre_BoxArrayArray:
 *   An array of box arrays.
 *   Since size can be zero, need to store ndim separately.
 *--------------------------------------------------------------------------*/

typedef struct hypre_BoxArrayArray_struct
{
   hypre_BoxArray  **box_arrays;    /* Array of pointers to box arrays */
   HYPRE_Int         size;          /* Size of box array array */
   HYPRE_Int         alloc_size;    /* Size of currently alloced space */
   HYPRE_Int         ndim;          /* number of dimensions */
   HYPRE_Int        *ids;           /* box array identifiers */
} hypre_BoxArrayArray;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_Index
 *--------------------------------------------------------------------------*/

#define hypre_IndexD(index, d)  (index[d])

/* Avoid using these macros */
#define hypre_IndexX(index)     hypre_IndexD(index, 0)
#define hypre_IndexY(index)     hypre_IndexD(index, 1)
#define hypre_IndexZ(index)     hypre_IndexD(index, 2)

/*--------------------------------------------------------------------------
 * Member functions: hypre_Index
 *--------------------------------------------------------------------------*/

/*----- Avoid using these Index macros -----*/

#define hypre_SetIndex3(index, ix, iy, iz) \
( hypre_IndexD(index, 0) = ix,\
  hypre_IndexD(index, 1) = iy,\
  hypre_IndexD(index, 2) = iz )

#define hypre_ClearIndex(index)  hypre_SetIndex(index, 0)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_Box
 *--------------------------------------------------------------------------*/

#define hypre_BoxIMin(box)     ((box) -> imin)
#define hypre_BoxIMax(box)     ((box) -> imax)
#define hypre_BoxNDim(box)     ((box) -> ndim)

#define hypre_BoxIMinD(box, d) (hypre_IndexD(hypre_BoxIMin(box), d))
#define hypre_BoxIMaxD(box, d) (hypre_IndexD(hypre_BoxIMax(box), d))
#define hypre_BoxSizeD(box, d) \
hypre_max(0, (hypre_BoxIMaxD(box, d) - hypre_BoxIMinD(box, d) + 1))

#define hypre_IndexDInBox(index, d, box) \
( hypre_IndexD(index, d) >= hypre_BoxIMinD(box, d) && \
  hypre_IndexD(index, d) <= hypre_BoxIMaxD(box, d) )

/* The first hypre_CCBoxIndexRank is better style because it is similar to
   hypre_BoxIndexRank.  The second one sometimes avoids compiler warnings. */
#define hypre_CCBoxIndexRank(box, index) 0
#define hypre_CCBoxIndexRank_noargs() 0
#define hypre_CCBoxOffsetDistance(box, index) 0

/*----- Avoid using these Box macros -----*/

#define hypre_BoxSizeX(box)    hypre_BoxSizeD(box, 0)
#define hypre_BoxSizeY(box)    hypre_BoxSizeD(box, 1)
#define hypre_BoxSizeZ(box)    hypre_BoxSizeD(box, 2)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_BoxArray
 *--------------------------------------------------------------------------*/

#define hypre_BoxArrayBoxes(box_array)     ((box_array) -> boxes)
#define hypre_BoxArrayBox(box_array, i)    &((box_array) -> boxes[(i)])
#define hypre_BoxArraySize(box_array)      ((box_array) -> size)
#define hypre_BoxArrayAllocSize(box_array) ((box_array) -> alloc_size)
#define hypre_BoxArrayNDim(box_array)      ((box_array) -> ndim)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_BoxArrayArray
 *--------------------------------------------------------------------------*/

#define hypre_BoxArrayArrayBoxArrays(box_array_array) \
((box_array_array) -> box_arrays)
#define hypre_BoxArrayArrayBoxArray(box_array_array, i) \
((box_array_array) -> box_arrays[(i)])
#define hypre_BoxArrayArraySize(box_array_array) \
((box_array_array) -> size)
#define hypre_BoxArrayArrayAllocSize(box_array_array) \
((box_array_array) -> alloc_size)
#define hypre_BoxArrayArrayNDim(box_array_array) \
((box_array_array) -> ndim)
#define hypre_BoxArrayArrayIDs(box_array_array) \
((box_array_array) -> ids)
#define hypre_BoxArrayArrayID(box_array_array, i) \
((box_array_array) -> ids[i])

/*--------------------------------------------------------------------------
 * Looping macros:
 *--------------------------------------------------------------------------*/

#define hypre_ForBoxI(i, box_array) \
for (i = 0; i < hypre_BoxArraySize(box_array); i++)

#define hypre_ForBoxArrayI(i, box_array_array) \
for (i = 0; i < hypre_BoxArrayArraySize(box_array_array); i++)

/*--------------------------------------------------------------------------
 * BoxLoop macros:
 *--------------------------------------------------------------------------*/

#if 0 /* set to 0 to use the new box loops */

#define HYPRE_BOX_PRIVATE hypre__nx,hypre__ny,hypre__nz,hypre__i,hypre__j,hypre__k

#define hypre_BoxLoopDeclareS(dbox, stride, sx, sy, sz) \
HYPRE_Int  sx = (hypre_IndexX(stride));\
HYPRE_Int  sy = (hypre_IndexY(stride)*hypre_BoxSizeX(dbox));\
HYPRE_Int  sz = (hypre_IndexZ(stride)*\
           hypre_BoxSizeX(dbox)*hypre_BoxSizeY(dbox))

#define hypre_BoxLoopDeclareN(loop_size) \
HYPRE_Int  hypre__i, hypre__j, hypre__k;\
HYPRE_Int  hypre__nx = hypre_IndexX(loop_size);\
HYPRE_Int  hypre__ny = hypre_IndexY(loop_size);\
HYPRE_Int  hypre__nz = hypre_IndexZ(loop_size);\
HYPRE_Int  hypre__mx = hypre__nx;\
HYPRE_Int  hypre__my = hypre__ny;\
HYPRE_Int  hypre__mz = hypre__nz;\
HYPRE_Int  hypre__dir, hypre__max;\
HYPRE_Int  hypre__div, hypre__mod;\
HYPRE_Int  hypre__block, hypre__num_blocks;\
hypre__dir = 0;\
hypre__max = hypre__nx;\
if (hypre__ny > hypre__max)\
{\
   hypre__dir = 1;\
   hypre__max = hypre__ny;\
}\
if (hypre__nz > hypre__max)\
{\
   hypre__dir = 2;\
   hypre__max = hypre__nz;\
}\
hypre__num_blocks = hypre_NumThreads();\
if (hypre__max < hypre__num_blocks)\
{\
   hypre__num_blocks = hypre__max;\
}\
if (hypre__num_blocks > 0)\
{\
   hypre__div = hypre__max / hypre__num_blocks;\
   hypre__mod = hypre__max % hypre__num_blocks;\
}

#define hypre_BoxLoopSet(i, j, k) \
i = 0;\
j = 0;\
k = 0;\
hypre__nx = hypre__mx;\
hypre__ny = hypre__my;\
hypre__nz = hypre__mz;\
if (hypre__num_blocks > 1)\
{\
   if (hypre__dir == 0)\
   {\
      i = hypre__block * hypre__div + hypre_min(hypre__mod, hypre__block);\
      hypre__nx = hypre__div + ((hypre__mod > hypre__block) ? 1 : 0);\
   }\
   else if (hypre__dir == 1)\
   {\
      j = hypre__block * hypre__div + hypre_min(hypre__mod, hypre__block);\
      hypre__ny = hypre__div + ((hypre__mod > hypre__block) ? 1 : 0);\
   }\
   else if (hypre__dir == 2)\
   {\
      k = hypre__block * hypre__div + hypre_min(hypre__mod, hypre__block);\
      hypre__nz = hypre__div + ((hypre__mod > hypre__block) ? 1 : 0);\
   }\
}

#define hypre_BoxLoopGetIndex(index) \
index[0] = hypre__i; index[1] = hypre__j; index[2] = hypre__k

/* Use this before the For macros below to force only one block */
#define hypre_BoxLoopSetOneBlock() hypre__num_blocks = 1

/* Use this to get the block iteration inside a BoxLoop */
#define hypre_BoxLoopBlock() hypre__block

/*-----------------------------------*/

#define hypre_BoxLoop0Begin(ndim, loop_size)\
{\
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop0For()\
   hypre__BoxLoop0For(hypre__i, hypre__j, hypre__k)
#define hypre__BoxLoop0For(i, j, k)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
   hypre_BoxLoopSet(i, j, k);\
   for (k = 0; k < hypre__nz; k++)\
   {\
      for (j = 0; j < hypre__ny; j++)\
      {\
         for (i = 0; i < hypre__nx; i++)\
         {

#define hypre_BoxLoop0End()\
         }\
      }\
   }\
   }\
}

/*-----------------------------------*/

#define hypre_BoxLoop1Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1)\
{\
   HYPRE_Int  hypre__i1start = hypre_BoxIndexRank(dbox1, start1);\
   hypre_BoxLoopDeclareS(dbox1, stride1, hypre__sx1, hypre__sy1, hypre__sz1);\
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop1For(i1)\
   hypre__BoxLoop1For(hypre__i, hypre__j, hypre__k, i1)
#define hypre__BoxLoop1For(i, j, k, i1)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
   hypre_BoxLoopSet(i, j, k);\
   i1 = hypre__i1start + i*hypre__sx1 + j*hypre__sy1 + k*hypre__sz1;\
   for (k = 0; k < hypre__nz; k++)\
   {\
      for (j = 0; j < hypre__ny; j++)\
      {\
         for (i = 0; i < hypre__nx; i++)\
         {

#define hypre_BoxLoop1End(i1)\
            i1 += hypre__sx1;\
         }\
         i1 += hypre__sy1 - hypre__nx*hypre__sx1;\
      }\
      i1 += hypre__sz1 - hypre__ny*hypre__sy1;\
   }\
   }\
}

/*-----------------------------------*/

#define hypre_BoxLoop2Begin(ndim,loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2)\
{\
   HYPRE_Int  hypre__i1start = hypre_BoxIndexRank(dbox1, start1);\
   HYPRE_Int  hypre__i2start = hypre_BoxIndexRank(dbox2, start2);\
   hypre_BoxLoopDeclareS(dbox1, stride1, hypre__sx1, hypre__sy1, hypre__sz1);\
   hypre_BoxLoopDeclareS(dbox2, stride2, hypre__sx2, hypre__sy2, hypre__sz2);\
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop2For(i1, i2)\
   hypre__BoxLoop2For(hypre__i, hypre__j, hypre__k, i1, i2)
#define hypre__BoxLoop2For(i, j, k, i1, i2)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
   hypre_BoxLoopSet(i, j, k);\
   i1 = hypre__i1start + i*hypre__sx1 + j*hypre__sy1 + k*hypre__sz1;\
   i2 = hypre__i2start + i*hypre__sx2 + j*hypre__sy2 + k*hypre__sz2;\
   for (k = 0; k < hypre__nz; k++)\
   {\
      for (j = 0; j < hypre__ny; j++)\
      {\
         for (i = 0; i < hypre__nx; i++)\
         {

#define hypre_BoxLoop2End(i1, i2)\
            i1 += hypre__sx1;\
            i2 += hypre__sx2;\
         }\
         i1 += hypre__sy1 - hypre__nx*hypre__sx1;\
         i2 += hypre__sy2 - hypre__nx*hypre__sx2;\
      }\
      i1 += hypre__sz1 - hypre__ny*hypre__sy1;\
      i2 += hypre__sz2 - hypre__ny*hypre__sy2;\
   }\
   }\
}

/*-----------------------------------*/

#define hypre_BoxLoop3Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2,\
                            dbox3, start3, stride3, i3)\
{\
   HYPRE_Int  hypre__i1start = hypre_BoxIndexRank(dbox1, start1);\
   HYPRE_Int  hypre__i2start = hypre_BoxIndexRank(dbox2, start2);\
   HYPRE_Int  hypre__i3start = hypre_BoxIndexRank(dbox3, start3);\
   hypre_BoxLoopDeclareS(dbox1, stride1, hypre__sx1, hypre__sy1, hypre__sz1);\
   hypre_BoxLoopDeclareS(dbox2, stride2, hypre__sx2, hypre__sy2, hypre__sz2);\
   hypre_BoxLoopDeclareS(dbox3, stride3, hypre__sx3, hypre__sy3, hypre__sz3);\
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop3For(i1, i2, i3)\
   hypre__BoxLoop3For(hypre__i, hypre__j, hypre__k, i1, i2, i3)
#define hypre__BoxLoop3For(i, j, k, i1, i2, i3)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
   hypre_BoxLoopSet(i, j, k);\
   i1 = hypre__i1start + i*hypre__sx1 + j*hypre__sy1 + k*hypre__sz1;\
   i2 = hypre__i2start + i*hypre__sx2 + j*hypre__sy2 + k*hypre__sz2;\
   i3 = hypre__i3start + i*hypre__sx3 + j*hypre__sy3 + k*hypre__sz3;\
   for (k = 0; k < hypre__nz; k++)\
   {\
      for (j = 0; j < hypre__ny; j++)\
      {\
         for (i = 0; i < hypre__nx; i++)\
         {

#define hypre_BoxLoop3End(i1, i2, i3)\
            i1 += hypre__sx1;\
            i2 += hypre__sx2;\
            i3 += hypre__sx3;\
         }\
         i1 += hypre__sy1 - hypre__nx*hypre__sx1;\
         i2 += hypre__sy2 - hypre__nx*hypre__sx2;\
         i3 += hypre__sy3 - hypre__nx*hypre__sx3;\
      }\
      i1 += hypre__sz1 - hypre__ny*hypre__sy1;\
      i2 += hypre__sz2 - hypre__ny*hypre__sy2;\
      i3 += hypre__sz3 - hypre__ny*hypre__sy3;\
   }\
   }\
}

/*-----------------------------------*/

#define hypre_BoxLoop4Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2,\
                            dbox3, start3, stride3, i3,\
                            dbox4, start4, stride4, i4)\
{\
   HYPRE_Int  hypre__i1start = hypre_BoxIndexRank(dbox1, start1);\
   HYPRE_Int  hypre__i2start = hypre_BoxIndexRank(dbox2, start2);\
   HYPRE_Int  hypre__i3start = hypre_BoxIndexRank(dbox3, start3);\
   HYPRE_Int  hypre__i4start = hypre_BoxIndexRank(dbox4, start4);\
   hypre_BoxLoopDeclareS(dbox1, stride1, hypre__sx1, hypre__sy1, hypre__sz1);\
   hypre_BoxLoopDeclareS(dbox2, stride2, hypre__sx2, hypre__sy2, hypre__sz2);\
   hypre_BoxLoopDeclareS(dbox3, stride3, hypre__sx3, hypre__sy3, hypre__sz3);\
   hypre_BoxLoopDeclareS(dbox4, stride4, hypre__sx4, hypre__sy4, hypre__sz4);\
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop4For(i1, i2, i3, i4)\
   hypre__BoxLoop4For(hypre__i, hypre__j, hypre__k, i1, i2, i3, i4)
#define hypre__BoxLoop4For(i, j, k, i1, i2, i3, i4)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
   hypre_BoxLoopSet(i, j, k);\
   i1 = hypre__i1start + i*hypre__sx1 + j*hypre__sy1 + k*hypre__sz1;\
   i2 = hypre__i2start + i*hypre__sx2 + j*hypre__sy2 + k*hypre__sz2;\
   i3 = hypre__i3start + i*hypre__sx3 + j*hypre__sy3 + k*hypre__sz3;\
   i4 = hypre__i4start + i*hypre__sx4 + j*hypre__sy4 + k*hypre__sz4;\
   for (k = 0; k < hypre__nz; k++)\
   {\
      for (j = 0; j < hypre__ny; j++)\
      {\
         for (i = 0; i < hypre__nx; i++)\
         {

#define hypre_BoxLoop4End(i1, i2, i3, i4)\
            i1 += hypre__sx1;\
            i2 += hypre__sx2;\
            i3 += hypre__sx3;\
            i4 += hypre__sx4;\
         }\
         i1 += hypre__sy1 - hypre__nx*hypre__sx1;\
         i2 += hypre__sy2 - hypre__nx*hypre__sx2;\
         i3 += hypre__sy3 - hypre__nx*hypre__sx3;\
         i4 += hypre__sy4 - hypre__nx*hypre__sx4;\
      }\
      i1 += hypre__sz1 - hypre__ny*hypre__sy1;\
      i2 += hypre__sz2 - hypre__ny*hypre__sy2;\
      i3 += hypre__sz3 - hypre__ny*hypre__sy3;\
      i4 += hypre__sz4 - hypre__ny*hypre__sy4;\
   }\
   }\
}

/*-----------------------------------*/

#else

#define HYPRE_BOX_PRIVATE        ZYPRE_BOX_PRIVATE

#define hypre_BoxLoopGetIndex    zypre_BoxLoopGetIndex
#define hypre_BoxLoopSetOneBlock zypre_BoxLoopSetOneBlock
#define hypre_BoxLoopBlock       zypre_BoxLoopBlock
#define hypre_BoxLoop0Begin      zypre_BoxLoop0Begin
#define hypre_BoxLoop0For        zypre_BoxLoop0For
#define hypre_BoxLoop0End        zypre_BoxLoop0End
#define hypre_BoxLoop1Begin      zypre_BoxLoop1Begin
#define hypre_BoxLoop1For        zypre_BoxLoop1For
#define hypre_BoxLoop1End        zypre_BoxLoop1End
#define hypre_BoxLoop2Begin      zypre_BoxLoop2Begin
#define hypre_BoxLoop2For        zypre_BoxLoop2For
#define hypre_BoxLoop2End        zypre_BoxLoop2End
#define hypre_BoxLoop3Begin      zypre_BoxLoop3Begin
#define hypre_BoxLoop3For        zypre_BoxLoop3For
#define hypre_BoxLoop3End        zypre_BoxLoop3End
#define hypre_BoxLoop4Begin      zypre_BoxLoop4Begin
#define hypre_BoxLoop4For        zypre_BoxLoop4For
#define hypre_BoxLoop4End        zypre_BoxLoop4End

#endif /* end if 1 */

#endif

/******************************************************************************
 *
 * NEW BoxLoop STUFF
 *
 *****************************************************************************/

#ifndef hypre_ZBOX_HEADER
#define hypre_ZBOX_HEADER

#define ZYPRE_BOX_PRIVATE hypre__IN,hypre__JN,hypre__I,hypre__J,hypre__d,hypre__i

/*--------------------------------------------------------------------------
 * BoxLoop macros:
 *--------------------------------------------------------------------------*/

#define zypre_BoxLoopDeclare() \
HYPRE_Int  hypre__tot, hypre__div, hypre__mod;\
HYPRE_Int  hypre__block, hypre__num_blocks;\
HYPRE_Int  hypre__d, hypre__ndim;\
HYPRE_Int  hypre__I, hypre__J, hypre__IN, hypre__JN;\
HYPRE_Int  hypre__i[HYPRE_MAXDIM+1], hypre__n[HYPRE_MAXDIM+1]

#define zypre_BoxLoopDeclareK(k) \
HYPRE_Int  hypre__ikstart##k, hypre__i0inc##k;\
HYPRE_Int  hypre__sk##k[HYPRE_MAXDIM], hypre__ikinc##k[HYPRE_MAXDIM+1]

#define zypre_BoxLoopInit(ndim, loop_size) \
hypre__ndim = ndim;\
hypre__n[0] = loop_size[0];\
hypre__tot = 1;\
for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
{\
   hypre__n[hypre__d] = loop_size[hypre__d];\
   hypre__tot *= hypre__n[hypre__d];\
}\
hypre__n[hypre__ndim] = 2;\
hypre__num_blocks = hypre_NumThreads();\
if (hypre__tot < hypre__num_blocks)\
{\
   hypre__num_blocks = hypre__tot;\
}\
if (hypre__num_blocks > 0)\
{\
   hypre__div = hypre__tot / hypre__num_blocks;\
   hypre__mod = hypre__tot % hypre__num_blocks;\
}

#define zypre_BoxLoopInitK(k, dboxk, startk, stridek, ik) \
hypre__sk##k[0] = stridek[0];\
hypre__ikinc##k[0] = 0;\
ik = hypre_BoxSizeD(dboxk, 0); /* temporarily use ik */\
for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
{\
   hypre__sk##k[hypre__d] = ik*stridek[hypre__d];\
   hypre__ikinc##k[hypre__d] = hypre__ikinc##k[hypre__d-1] +\
      hypre__sk##k[hypre__d] - hypre__n[hypre__d-1]*hypre__sk##k[hypre__d-1];\
   ik *= hypre_BoxSizeD(dboxk, hypre__d);\
}\
hypre__i0inc##k = hypre__sk##k[0];\
hypre__ikinc##k[hypre__ndim] = 0;\
hypre__ikstart##k = hypre_BoxIndexRank(dboxk, startk)

#define zypre_BoxLoopSet() \
hypre__IN = hypre__n[0];\
if (hypre__num_blocks > 1)/* in case user sets num_blocks to 1 */\
{\
   hypre__JN = hypre__div + ((hypre__mod > hypre__block) ? 1 : 0);\
   hypre__J = hypre__block * hypre__div + hypre_min(hypre__mod, hypre__block);\
   for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
   {\
      hypre__i[hypre__d] = hypre__J % hypre__n[hypre__d];\
      hypre__J /= hypre__n[hypre__d];\
   }\
}\
else\
{\
   hypre__JN = hypre__tot;\
   for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
   {\
      hypre__i[hypre__d] = 0;\
   }\
}\
hypre__i[hypre__ndim] = 0

#define zypre_BoxLoopSetK(k, ik) \
ik = hypre__ikstart##k;\
for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
{\
   ik += hypre__i[hypre__d]*hypre__sk##k[hypre__d];\
}

#define zypre_BoxLoopInc1() \
hypre__d = 1;\
while ((hypre__i[hypre__d]+2) > hypre__n[hypre__d])\
{\
   hypre__d++;\
}

#define zypre_BoxLoopInc2() \
hypre__i[hypre__d]++;\
while (hypre__d > 1)\
{\
   hypre__d--;\
   hypre__i[hypre__d] = 0;\
}

/* This returns the loop index (of type hypre_Index) for the current iteration,
 * where the numbering starts at 0.  It works even when threading is turned on,
 * as long as 'index' is declared to be private. */
#define zypre_BoxLoopGetIndex(index) \
index[0] = hypre__I;\
for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
{\
   index[hypre__d] = hypre__i[hypre__d];\
}

/* Use this before the For macros below to force only one block */
#define zypre_BoxLoopSetOneBlock() hypre__num_blocks = 1

/* Use this to get the block iteration inside a BoxLoop */
#define zypre_BoxLoopBlock() hypre__block

/*-----------------------------------*/

#define zypre_BoxLoop0Begin(ndim, loop_size)\
{\
   zypre_BoxLoopDeclare();\
   zypre_BoxLoopInit(ndim, loop_size);

#define zypre_BoxLoop0For()\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define zypre_BoxLoop0End()\
         }\
         zypre_BoxLoopInc1();\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/

#define zypre_BoxLoop1Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1)\
{\
   zypre_BoxLoopDeclare();\
   zypre_BoxLoopDeclareK(1);\
   zypre_BoxLoopInit(ndim, loop_size);\
   zypre_BoxLoopInitK(1, dbox1, start1, stride1, i1);

#define zypre_BoxLoop1For(i1)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      zypre_BoxLoopSetK(1, i1);\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define zypre_BoxLoop1End(i1)\
            i1 += hypre__i0inc1;\
         }\
         zypre_BoxLoopInc1();\
         i1 += hypre__ikinc1[hypre__d];\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/

#define zypre_BoxLoop2Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2)\
{\
   zypre_BoxLoopDeclare();\
   zypre_BoxLoopDeclareK(1);\
   zypre_BoxLoopDeclareK(2);\
   zypre_BoxLoopInit(ndim, loop_size);\
   zypre_BoxLoopInitK(1, dbox1, start1, stride1, i1);\
   zypre_BoxLoopInitK(2, dbox2, start2, stride2, i2);

#define zypre_BoxLoop2For(i1, i2)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      zypre_BoxLoopSetK(1, i1);\
      zypre_BoxLoopSetK(2, i2);\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define zypre_BoxLoop2End(i1, i2)\
            i1 += hypre__i0inc1;\
            i2 += hypre__i0inc2;\
         }\
         zypre_BoxLoopInc1();\
         i1 += hypre__ikinc1[hypre__d];\
         i2 += hypre__ikinc2[hypre__d];\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/

#define zypre_BoxLoop3Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2,\
                            dbox3, start3, stride3, i3)\
{\
   zypre_BoxLoopDeclare();\
   zypre_BoxLoopDeclareK(1);\
   zypre_BoxLoopDeclareK(2);\
   zypre_BoxLoopDeclareK(3);\
   zypre_BoxLoopInit(ndim, loop_size);\
   zypre_BoxLoopInitK(1, dbox1, start1, stride1, i1);\
   zypre_BoxLoopInitK(2, dbox2, start2, stride2, i2);\
   zypre_BoxLoopInitK(3, dbox3, start3, stride3, i3);

#define zypre_BoxLoop3For(i1, i2, i3)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      zypre_BoxLoopSetK(1, i1);\
      zypre_BoxLoopSetK(2, i2);\
      zypre_BoxLoopSetK(3, i3);\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define zypre_BoxLoop3End(i1, i2, i3)\
            i1 += hypre__i0inc1;\
            i2 += hypre__i0inc2;\
            i3 += hypre__i0inc3;\
         }\
         zypre_BoxLoopInc1();\
         i1 += hypre__ikinc1[hypre__d];\
         i2 += hypre__ikinc2[hypre__d];\
         i3 += hypre__ikinc3[hypre__d];\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/

#define zypre_BoxLoop4Begin(ndim, loop_size,\
                            dbox1, start1, stride1, i1,\
                            dbox2, start2, stride2, i2,\
                            dbox3, start3, stride3, i3,\
                            dbox4, start4, stride4, i4)\
{\
   zypre_BoxLoopDeclare();\
   zypre_BoxLoopDeclareK(1);\
   zypre_BoxLoopDeclareK(2);\
   zypre_BoxLoopDeclareK(3);\
   zypre_BoxLoopDeclareK(4);\
   zypre_BoxLoopInit(ndim, loop_size);\
   zypre_BoxLoopInitK(1, dbox1, start1, stride1, i1);\
   zypre_BoxLoopInitK(2, dbox2, start2, stride2, i2);\
   zypre_BoxLoopInitK(3, dbox3, start3, stride3, i3);\
   zypre_BoxLoopInitK(4, dbox4, start4, stride4, i4);

#define zypre_BoxLoop4For(i1, i2, i3, i4)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      zypre_BoxLoopSetK(1, i1);\
      zypre_BoxLoopSetK(2, i2);\
      zypre_BoxLoopSetK(3, i3);\
      zypre_BoxLoopSetK(4, i4);\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define zypre_BoxLoop4End(i1, i2, i3, i4)\
            i1 += hypre__i0inc1;\
            i2 += hypre__i0inc2;\
            i3 += hypre__i0inc3;\
            i4 += hypre__i0inc4;\
         }\
         zypre_BoxLoopInc1();\
         i1 += hypre__ikinc1[hypre__d];\
         i2 += hypre__ikinc2[hypre__d];\
         i3 += hypre__ikinc3[hypre__d];\
         i4 += hypre__ikinc4[hypre__d];\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/
/* currently hardcoded for m <= 4 */

#define hypre_BoxLoopMBegin(m, ndim, loop_size,    \
                            dbox, start, stride, i)\
{\
   zypre_BoxLoopDeclare();\
   HYPRE_Int  hypre__ikstart[4], hypre__i0inc[4];\
   HYPRE_Int  hypre__sk[4][HYPRE_MAXDIM], hypre__ikinc[4][HYPRE_MAXDIM+1];\
   HYPRE_Int  hypre__k = 0;\
   HYPRE_Int  hypre__m = m;\
   zypre_BoxLoopInit(ndim, loop_size);\
   for (hypre__k = 0; hypre__k < hypre__m; hypre__k++)\
   {\
      hypre__sk[hypre__k][0] = stride[hypre__k][0];\
      hypre__ikinc[hypre__k][0] = 0;\
      i[hypre__k] = hypre_BoxSizeD(dbox[hypre__k], 0); /* temporarily use i */\
      for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
      {\
         hypre__sk[hypre__k][hypre__d] = i[hypre__k]*stride[hypre__k][hypre__d];\
         hypre__ikinc[hypre__k][hypre__d] =\
            hypre__ikinc[hypre__k][hypre__d-1] + hypre__sk[hypre__k][hypre__d] -\
            hypre__n[hypre__d-1]*hypre__sk[hypre__k][hypre__d-1];\
         i[hypre__k] *= hypre_BoxSizeD(dbox[hypre__k], hypre__d);\
      }\
      hypre__i0inc[hypre__k] = hypre__sk[hypre__k][0];\
      hypre__ikinc[hypre__k][hypre__ndim] = 0;\
      hypre__ikstart[hypre__k] =\
         hypre_BoxIndexRank(dbox[hypre__k], start[hypre__k]);\
   }

#define hypre_BoxLoopMFor(i)\
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)\
   {\
      zypre_BoxLoopSet();\
      for (hypre__k = 0; hypre__k < hypre__m; hypre__k++)\
      {\
         i[hypre__k] = hypre__ikstart[hypre__k];\
         for (hypre__d = 1; hypre__d < hypre__ndim; hypre__d++)\
         {\
            i[hypre__k] += hypre__i[hypre__d]*hypre__sk[hypre__k][hypre__d];\
         }\
      }\
      for (hypre__J = 0; hypre__J < hypre__JN; hypre__J++)\
      {\
         for (hypre__I = 0; hypre__I < hypre__IN; hypre__I++)\
         {

#define hypre_BoxLoopMEnd(i)\
            for (hypre__k = 0; hypre__k < hypre__m; hypre__k++)\
            {\
               i[hypre__k] += hypre__i0inc[hypre__k];\
            }\
         }\
         zypre_BoxLoopInc1();\
         for (hypre__k = 0; hypre__k < hypre__m; hypre__k++)\
         {\
            i[hypre__k] += hypre__ikinc[hypre__k][hypre__d];\
         }\
         zypre_BoxLoopInc2();\
      }\
   }\
}

/*-----------------------------------*/

#endif




/*--------------------------------------------------------------------------
 * NOTES - Keep these for reference here and elsewhere in the code
 *--------------------------------------------------------------------------*/

#if 0

#define hypre_BoxLoop2Begin(loop_size,
                            dbox1, start1, stride1, i1,
                            dbox2, start2, stride2, i2)
{
   /* init hypre__i1start */
   HYPRE_Int  hypre__i1start = hypre_BoxIndexRank(dbox1, start1);
   HYPRE_Int  hypre__i2start = hypre_BoxIndexRank(dbox2, start2);
   /* declare and set hypre__s1 */
   hypre_BoxLoopDeclareS(dbox1, stride1, hypre__sx1, hypre__sy1, hypre__sz1);
   hypre_BoxLoopDeclareS(dbox2, stride2, hypre__sx2, hypre__sy2, hypre__sz2);
   /* declare and set hypre__n, hypre__m, hypre__dir, hypre__max,
    *                 hypre__div, hypre__mod, hypre__block, hypre__num_blocks */
   hypre_BoxLoopDeclareN(loop_size);

#define hypre_BoxLoop2For(i, j, k, i1, i2)
   for (hypre__block = 0; hypre__block < hypre__num_blocks; hypre__block++)
   {
   /* set i and hypre__n */
   hypre_BoxLoopSet(i, j, k);
   /* set i1 */
   i1 = hypre__i1start + i*hypre__sx1 + j*hypre__sy1 + k*hypre__sz1;
   i2 = hypre__i2start + i*hypre__sx2 + j*hypre__sy2 + k*hypre__sz2;
   for (k = 0; k < hypre__nz; k++)
   {
      for (j = 0; j < hypre__ny; j++)
      {
         for (i = 0; i < hypre__nx; i++)
         {

#define hypre_BoxLoop2End(i1, i2)
            i1 += hypre__sx1;
            i2 += hypre__sx2;
         }
         i1 += hypre__sy1 - hypre__nx*hypre__sx1;
         i2 += hypre__sy2 - hypre__nx*hypre__sx2;
      }
      i1 += hypre__sz1 - hypre__ny*hypre__sy1;
      i2 += hypre__sz2 - hypre__ny*hypre__sy2;
   }
   }
}

/*----------------------------------------
 * Idea 2: Simple version of Idea 3 below
 *----------------------------------------*/

N = 1;
for (d = 0; d < ndim; d++)
{
   N *= n[d];
   i[d] = 0;
   n[d] -= 2; /* this produces a simpler comparison below */
}
i[ndim] = 0;
n[ndim] = 0;
for (I = 0; I < N; I++)
{
   /* loop body */

   for (d = 0; i[d] > n[d]; d++)
   {
      i[d] = 0;
   }
   i[d]++;
   i1 += s1[d]; /* NOTE: These are different from hypre__sx1, etc. above */
   i2 += s2[d]; /* The lengths of i, n, and s must be (ndim+1) */
}

/*----------------------------------------
 * Idea 3: Approach used in the box loops
 *----------------------------------------*/

N = 1;
for (d = 1; d < ndim; d++)
{
   N *= n[d];
   i[d] = 0;
   n[d] -= 2; /* this produces a simpler comparison below */
}
i[ndim] = 0;
n[ndim] = 0;
for (J = 0; J < N; J++)
{
   for (I = 0; I < n[0]; I++)
   {
      /* loop body */

      i1 += s1[0];
      i2 += s2[0];
   }
   for (d = 1; i[d] > n[d]; d++)
   {
      i[d] = 0;
   }
   i[d]++;
   i1 += s1[d]; /* NOTE: These are different from hypre__sx1, etc. above */
   i2 += s2[d]; /* The lengths of i, n, and s must be (ndim+1) */
}

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for the struct assumed partition
 *
 *****************************************************************************/

#ifndef hypre_ASSUMED_PART_HEADER
#define hypre_ASSUMED_PART_HEADER

typedef struct
{
   /* the entries will be the same for all procs */
   HYPRE_Int           ndim;             /* number of dimensions */
   hypre_BoxArray     *regions;          /* areas of the grid with boxes */
   HYPRE_Int           num_regions;      /* how many regions */
   HYPRE_Int          *proc_partitions;  /* proc ids assigned to each region
                                            (this is size num_regions +1) */
   hypre_Index        *divisions;        /* number of proc divisions in each
                                            direction for each region */

   hypre_Index         origin, stride;   /* coarsening parameters for the AP */

   /* these entries are specific to each proc */
   hypre_BoxArray     *my_partition;        /* my portion of grid (at most 2) */
   hypre_BoxArray     *my_partition_boxes;  /* boxes in my portion */
   HYPRE_Int          *my_partition_proc_ids;
   HYPRE_Int           my_partition_ids_size;
   HYPRE_Int           my_partition_ids_alloc;
   HYPRE_Int           my_partition_num_distinct_procs;

} hypre_StructAssumedPart;


/*Accessor macros */

#define hypre_StructAssumedPartNDim(apart) ((apart)->ndim)
#define hypre_StructAssumedPartRegions(apart) ((apart)->regions)
#define hypre_StructAssumedPartNumRegions(apart) ((apart)->num_regions)
#define hypre_StructAssumedPartDivisions(apart) ((apart)->divisions)
#define hypre_StructAssumedPartDivision(apart, i) ((apart)->divisions[i])
#define hypre_StructAssumedPartProcPartitions(apart) ((apart)->proc_partitions)
#define hypre_StructAssumedPartProcPartition(apart, i) ((apart)->proc_partitions[i])
#define hypre_StructAssumedPartOrigin(apart) ((apart)->origin)
#define hypre_StructAssumedPartStride(apart) ((apart)->stride)
#define hypre_StructAssumedPartMyPartition(apart) ((apart)->my_partition)
#define hypre_StructAssumedPartMyPartitionBoxes(apart) ((apart)->my_partition_boxes)
#define hypre_StructAssumedPartMyPartitionProcIds(apart) ((apart)->my_partition_proc_ids)
#define hypre_StructAssumedPartMyPartitionIdsSize(apart) ((apart)->my_partition_ids_size)
#define hypre_StructAssumedPartMyPartitionIdsAlloc(apart) ((apart)->my_partition_ids_alloc)
#define hypre_StructAssumedPartMyPartitionNumDistinctProcs(apart) ((apart)->my_partition_num_distinct_procs)

#define hypre_StructAssumedPartMyPartitionProcId(apart, i) ((apart)->my_partition_proc_ids[i])
#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

#ifndef hypre_BOX_MANAGER_HEADER
#define hypre_BOX_MANAGER_HEADER

/*--------------------------------------------------------------------------
 * BoxManEntry
 *--------------------------------------------------------------------------*/

typedef struct hypre_BoxManEntry_struct
{
   hypre_Index imin; /* Extents of box */
   hypre_Index imax;
   HYPRE_Int   ndim; /* Number of dimensions */

   HYPRE_Int proc; /* This is a two-part unique id: (proc, id) */
   HYPRE_Int id;
   HYPRE_Int num_ghost[2*HYPRE_MAXDIM];

   HYPRE_Int position; /* This indicates the location of the entry in the the
                        * box manager entries array and is used for pairing with
                        * the info object (populated in addentry) */

   void *boxman; /* The owning manager (populated in addentry) */

   struct hypre_BoxManEntry_struct  *next;

} hypre_BoxManEntry;

/*---------------------------------------------------------------------------
 * Box Manager: organizes arbitrary information in a spatial way
 *----------------------------------------------------------------------------*/

typedef struct
{
   MPI_Comm            comm;

   HYPRE_Int           max_nentries; /* storage allocated for entries */

   HYPRE_Int           is_gather_called; /* Boolean to indicate whether
                                            GatherEntries function has been
                                            called (prior to assemble) - may not
                                            want this (can tell by the size of
                                            gather_regions array) */

   hypre_BoxArray     *gather_regions; /* This is where we collect boxes input
                                          by calls to BoxManGatherEntries - to
                                          be gathered in the assemble.  These
                                          are then deleted after the assemble */


   HYPRE_Int           all_global_known; /* Boolean to say that every processor
                                            already has all of the global data
                                            for this manager (this could be
                                            accessed by a coarsening routine,
                                            for example) */

   HYPRE_Int           is_entries_sort; /* Boolean to say that entries were
                                           added in sorted order (id, proc)
                                           (this could be accessed by a
                                           coarsening routine, for example) */

   HYPRE_Int           entry_info_size; /* In bytes, the (max) size of the info
                                           object for the entries */

   HYPRE_Int           is_assembled; /* Flag to indicate if the box manager has
                                        been assembled (used to control whether
                                        or not functions can be used prior to
                                        assemble) */

   /* Storing the entries */
   HYPRE_Int          nentries; /* Number of entries stored */
   hypre_BoxManEntry *entries;  /* Actual box manager entries - sorted by
                                   (proc, id) at the end of the assemble) */

   HYPRE_Int         *procs_sort; /* The sorted procs corresponding to entries */
   HYPRE_Int         *ids_sort; /* Sorted ids corresponding to the entries */

   HYPRE_Int          num_procs_sort; /* Number of distinct procs in entries */
   HYPRE_Int         *procs_sort_offsets; /* Offsets for procs into the
                                             entry_sort array */
   HYPRE_Int          first_local; /* Position of local infomation in entries */
   HYPRE_Int          local_proc_offset; /* Position of local information in
                                            offsets */

   /* Here is the table  that organizes the entries spatially (by index) */
   hypre_BoxManEntry **index_table; /* This points into 'entries' array and
                                       corresponds to the index arays */

   HYPRE_Int          *indexes[HYPRE_MAXDIM]; /* Indexes (ordered) for imin and
                                                 imax of each box in the entries
                                                 array */
   HYPRE_Int           size[HYPRE_MAXDIM]; /* How many indexes in each
                                              direction */

   HYPRE_Int           last_index[HYPRE_MAXDIM]; /* Last index used in the
                                                    indexes map */

   HYPRE_Int           num_my_entries; /* Num entries with proc_id = myid */
   HYPRE_Int          *my_ids; /* Array of ids corresponding to my entries */
   hypre_BoxManEntry **my_entries; /* Points into entries that are mine and
                                      corresponds to my_ids array.  This is
                                      destroyed in the assemble. */

   void               *info_objects; /* Array of info objects (each of size
                                        entry_info_size), managed byte-wise */

   hypre_StructAssumedPart *assumed_partition; /* The assumed partition object.
                                                  For now this is only used
                                                  during the assemble (where it
                                                  is created). */
   HYPRE_Int           ndim; /* Problem dimension (known in the grid) */

   hypre_Box          *bounding_box; /* Bounding box from associated grid */

   HYPRE_Int           next_id; /* Counter to indicate the next id that would be
                                   unique (regardless of proc id) */

   /* Ghost stuff  */
   HYPRE_Int           num_ghost[2*HYPRE_MAXDIM];

} hypre_BoxManager;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_BoxMan
 *--------------------------------------------------------------------------*/

#define hypre_BoxManComm(manager)               ((manager) -> comm)

#define hypre_BoxManMaxNEntries(manager)        ((manager) -> max_nentries)

#define hypre_BoxManIsGatherCalled(manager)     ((manager) -> is_gather_called)
#define hypre_BoxManIsEntriesSort(manager)      ((manager) -> is_entries_sort)
#define hypre_BoxManGatherRegions(manager)      ((manager) -> gather_regions)
#define hypre_BoxManAllGlobalKnown(manager)     ((manager) -> all_global_known)
#define hypre_BoxManEntryInfoSize(manager)      ((manager) -> entry_info_size)
#define hypre_BoxManNEntries(manager)           ((manager) -> nentries)
#define hypre_BoxManEntries(manager)            ((manager) -> entries)
#define hypre_BoxManInfoObjects(manager)        ((manager) -> info_objects)
#define hypre_BoxManIsAssembled(manager)        ((manager) -> is_assembled)

#define hypre_BoxManProcsSort(manager)          ((manager) -> procs_sort)
#define hypre_BoxManIdsSort(manager)            ((manager) -> ids_sort)
#define hypre_BoxManNumProcsSort(manager)       ((manager) -> num_procs_sort)
#define hypre_BoxManProcsSortOffsets(manager)   ((manager) -> procs_sort_offsets)
#define hypre_BoxManLocalProcOffset(manager)    ((manager) -> local_proc_offset)

#define hypre_BoxManFirstLocal(manager)         ((manager) -> first_local)

#define hypre_BoxManIndexTable(manager)         ((manager) -> index_table)
#define hypre_BoxManIndexes(manager)            ((manager) -> indexes)
#define hypre_BoxManSize(manager)               ((manager) -> size)
#define hypre_BoxManLastIndex(manager)          ((manager) -> last_index)

#define hypre_BoxManNumMyEntries(manager)       ((manager) -> num_my_entries)
#define hypre_BoxManMyIds(manager)              ((manager) -> my_ids)
#define hypre_BoxManMyEntries(manager)          ((manager) -> my_entries)
#define hypre_BoxManAssumedPartition(manager)   ((manager) -> assumed_partition)
#define hypre_BoxManNDim(manager)               ((manager) -> ndim)
#define hypre_BoxManBoundingBox(manager)        ((manager) -> bounding_box)

#define hypre_BoxManNextId(manager)             ((manager) -> next_id)

#define hypre_BoxManNumGhost(manager)           ((manager) -> num_ghost)

#define hypre_BoxManIndexesD(manager, d)    hypre_BoxManIndexes(manager)[d]
#define hypre_BoxManSizeD(manager, d)       hypre_BoxManSize(manager)[d]
#define hypre_BoxManLastIndexD(manager, d)  hypre_BoxManLastIndex(manager)[d]

#define hypre_BoxManInfoObject(manager, i) \
(void *) ((char *)hypre_BoxManInfoObjects(manager) + i* hypre_BoxManEntryInfoSize(manager))

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_BoxManEntry
 *--------------------------------------------------------------------------*/

#define hypre_BoxManEntryIMin(entry)     ((entry) -> imin)
#define hypre_BoxManEntryIMax(entry)     ((entry) -> imax)
#define hypre_BoxManEntryNDim(entry)     ((entry) -> ndim)
#define hypre_BoxManEntryProc(entry)     ((entry) -> proc)
#define hypre_BoxManEntryId(entry)       ((entry) -> id)
#define hypre_BoxManEntryPosition(entry) ((entry) -> position)
#define hypre_BoxManEntryNumGhost(entry) ((entry) -> num_ghost)
#define hypre_BoxManEntryNext(entry)     ((entry) -> next)
#define hypre_BoxManEntryBoxMan(entry)   ((entry) -> boxman)

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/



/******************************************************************************
 *
 * Header info for the hypre_StructGrid structures
 *
 *****************************************************************************/

#ifndef hypre_STRUCT_GRID_HEADER
#define hypre_STRUCT_GRID_HEADER

/*--------------------------------------------------------------------------
 * hypre_StructGrid:
 *--------------------------------------------------------------------------*/

typedef struct hypre_StructGrid_struct
{
   MPI_Comm             comm;

   HYPRE_Int            ndim;         /* Number of grid dimensions */

   hypre_BoxArray      *boxes;        /* Array of boxes in this process */
   HYPRE_Int           *ids;          /* Unique IDs for boxes */
   hypre_Index          max_distance; /* Neighborhood size - in each dimension*/

   hypre_Box           *bounding_box; /* Bounding box around grid */

   HYPRE_Int            local_size;   /* Number of grid points locally */
   HYPRE_Int            global_size;  /* Total number of grid points */

   hypre_Index          periodic;     /* Indicates if grid is periodic */
   HYPRE_Int            num_periods;  /* number of box set periods */

   hypre_Index         *pshifts;      /* shifts of periodicity */


   HYPRE_Int            ref_count;


   HYPRE_Int            ghlocal_size; /* Number of vars in box including ghosts */
   HYPRE_Int            num_ghost[2*HYPRE_MAXDIM]; /* ghost layer size */

   hypre_BoxManager    *boxman;

} hypre_StructGrid;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_StructGrid
 *--------------------------------------------------------------------------*/

#define hypre_StructGridComm(grid)          ((grid) -> comm)
#define hypre_StructGridNDim(grid)          ((grid) -> ndim)
#define hypre_StructGridBoxes(grid)         ((grid) -> boxes)
#define hypre_StructGridIDs(grid)           ((grid) -> ids)
#define hypre_StructGridID(grid, i)         ((grid) -> ids[i])
#define hypre_StructGridMaxDistance(grid)   ((grid) -> max_distance)
#define hypre_StructGridBoundingBox(grid)   ((grid) -> bounding_box)
#define hypre_StructGridLocalSize(grid)     ((grid) -> local_size)
#define hypre_StructGridGlobalSize(grid)    ((grid) -> global_size)
#define hypre_StructGridPeriodic(grid)      ((grid) -> periodic)
#define hypre_StructGridNumPeriods(grid)    ((grid) -> num_periods)
#define hypre_StructGridPShifts(grid)       ((grid) -> pshifts)
#define hypre_StructGridPShift(grid, i)     ((grid) -> pshifts[i])
#define hypre_StructGridRefCount(grid)      ((grid) -> ref_count)
#define hypre_StructGridGhlocalSize(grid)   ((grid) -> ghlocal_size)
#define hypre_StructGridNumGhost(grid)      ((grid) -> num_ghost)
#define hypre_StructGridBoxMan(grid)        ((grid) -> boxman)

#define hypre_StructGridBox(grid, i) \
(hypre_BoxArrayBox(hypre_StructGridBoxes(grid), i))
#define hypre_StructGridNumBoxes(grid) \
(hypre_BoxArraySize(hypre_StructGridBoxes(grid)))

#define hypre_StructGridIDPeriod(grid) \
hypre_BoxNeighborsIDPeriod(hypre_StructGridNeighbors(grid))

/*--------------------------------------------------------------------------
 * Looping macros:
 *--------------------------------------------------------------------------*/

#define hypre_ForStructGridBoxI(i, grid) \
hypre_ForBoxI(i, hypre_StructGridBoxes(grid))

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for hypre_StructStencil data structures
 *
 *****************************************************************************/

#ifndef hypre_STRUCT_STENCIL_HEADER
#define hypre_STRUCT_STENCIL_HEADER

/*--------------------------------------------------------------------------
 * hypre_StructStencil
 *--------------------------------------------------------------------------*/

typedef struct hypre_StructStencil_struct
{
   hypre_Index   *shape;      /* Description of a stencil's shape */
   HYPRE_Int      size;       /* Number of stencil coefficients */
   HYPRE_Int      ndim;       /* Number of dimensions */
   HYPRE_Int      diag_entry; /* Index of the diagonal entry (zero offset) */

   HYPRE_Int      ref_count;

} hypre_StructStencil;

/*--------------------------------------------------------------------------
 * Accessor functions for the hypre_StructStencil structure
 *--------------------------------------------------------------------------*/

#define hypre_StructStencilShape(stencil)      ((stencil) -> shape)
#define hypre_StructStencilSize(stencil)       ((stencil) -> size)
#define hypre_StructStencilNDim(stencil)       ((stencil) -> ndim)
#define hypre_StructStencilDiagEntry(stencil)  ((stencil) -> diag_entry)
#define hypre_StructStencilRefCount(stencil)   ((stencil) -> ref_count)

#define hypre_StructStencilOffset(stencil, i) \
hypre_StructStencilShape(stencil)[i]

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

#ifndef hypre_COMMUNICATION_HEADER
#define hypre_COMMUNICATION_HEADER

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommStencil_struct
{
   HYPRE_Int   ndim;
   hypre_Box  *box;                 /* extents of data array */
   HYPRE_Int  *data;                /* non-zero values indicate communication */
   hypre_Index stride;
   HYPRE_Int   mgrow[HYPRE_MAXDIM]; /* amount to grow in the minus direction */
   HYPRE_Int   pgrow[HYPRE_MAXDIM]; /* amount to grow in the plus direction */

} hypre_CommStencil;

/*--------------------------------------------------------------------------
 *
 * For "reverse" communication, the following are not needed (may be NULL)
 *    send_rboxnums, send_rboxes, send_transforms
 *
 * For "forward" communication, the following are not needed (may be NULL)
 *    recv_rboxnums, recv_rboxes, recv_transforms
 *
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommInfo_struct
{
   HYPRE_Int              ndim;
   hypre_BoxArrayArray   *send_boxes;
   hypre_Index            send_stride;
   HYPRE_Int            **send_processes;
   HYPRE_Int            **send_rboxnums;
   hypre_BoxArrayArray   *send_rboxes;  /* send_boxes, some with periodic shift */

   hypre_BoxArrayArray   *recv_boxes;
   hypre_Index            recv_stride;
   HYPRE_Int            **recv_processes;
   HYPRE_Int            **recv_rboxnums;
   hypre_BoxArrayArray   *recv_rboxes;  /* recv_boxes, some with periodic shift */

   HYPRE_Int              num_transforms;  /* may be 0    = identity transform */
   hypre_Index           *coords;          /* may be NULL = identity transform */
   hypre_Index           *dirs;            /* may be NULL = identity transform */
   HYPRE_Int            **send_transforms; /* may be NULL = identity transform */
   HYPRE_Int            **recv_transforms; /* may be NULL = identity transform */

   HYPRE_Int              boxes_match;  /* true (>0) if each send box has a
                                         * matching box on the recv processor */

} hypre_CommInfo;

/*--------------------------------------------------------------------------
 * Note: The dimension of the data represented by CommEntry will often be
 * smaller than the original problem dimension.
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommEntry_struct
{
   HYPRE_Int  offset;                       /* offset for the data */
   HYPRE_Int  dim;                          /* dimension of the data */
   HYPRE_Int  length_array[HYPRE_MAXDIM+1];
   HYPRE_Int  stride_array[HYPRE_MAXDIM+1];
   HYPRE_Int *imap;                         /* index map for last dim values */

} hypre_CommEntry;

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommBlock_struct
{
   HYPRE_Int         bufsize;     /* message buffer size (in doubles) */
   HYPRE_Int         pfxsize;     /* message buffer prefix size (in doubles) */
   HYPRE_Int         ndim;
   HYPRE_Int         num_values;
   HYPRE_Int         num_entries;
   hypre_CommEntry  *entries;
   HYPRE_Int        *imaps;       /* length = (num_entries*num_values) */

   /* This is only needed until first send buffer prefix is packed */
   HYPRE_Int        *rem_boxnums; /* entry remote box numbers */
   hypre_Box        *rem_boxes;   /* entry remote boxes */
   HYPRE_Int        *rem_orders;  /* length = (num_entries*num_values) */

} hypre_CommBlock;

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommType_struct
{
   HYPRE_Int         first_comm;  /* is this the first communication? */
   HYPRE_Int         proc;
   HYPRE_Int         bufsize;     /* message buffer size (in doubles) */
   HYPRE_Int         ndim;
   HYPRE_Int         num_blocks;
   hypre_CommBlock  *blocks;

} hypre_CommType;

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommPkg_struct
{
   MPI_Comm          comm;
   HYPRE_Int         ndim;

   HYPRE_Int         num_sends;
   HYPRE_Int         num_recvs;
   hypre_CommType   *send_types;
   hypre_CommType   *recv_types;

   hypre_CommType   *copy_from_type;
   hypre_CommType   *copy_to_type;

   /* needed for setting recv entries after the first communication */
   HYPRE_Int         num_blocks;  /* arrays below are num_blocks x ... */
   hypre_Index      *recv_strides;
   hypre_BoxArray  **recv_data_spaces;  /* recv data dimensions (by box) */
   HYPRE_Int       **recv_data_offsets; /* offsets into recv data (by box) */
   HYPRE_Int        *boxes_match;       /* same meaning as in CommInfo */

} hypre_CommPkg;

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct hypre_CommHandle_struct
{
   hypre_CommPkg     *comm_pkg;
   HYPRE_Complex    **send_data;
   HYPRE_Complex    **recv_data;

   HYPRE_Int          num_requests;
   hypre_MPI_Request *requests;
   hypre_MPI_Status  *status;

   HYPRE_Complex    **send_buffers;
   HYPRE_Complex    **recv_buffers;

   /* set = 0, add = 1 */
   HYPRE_Int          action;

} hypre_CommHandle;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommStencil
 *--------------------------------------------------------------------------*/

#define hypre_CommStencilNDim(cstenc)   (cstenc -> ndim)
#define hypre_CommStencilBox(cstenc)    (cstenc -> box)
#define hypre_CommStencilData(cstenc)   (cstenc -> data)
#define hypre_CommStencilStride(cstenc) (cstenc -> stride)
#define hypre_CommStencilMGrow(cstenc)  (cstenc -> mgrow)
#define hypre_CommStencilPGrow(cstenc)  (cstenc -> pgrow)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommInfo
 *--------------------------------------------------------------------------*/

#define hypre_CommInfoNDim(info)           (info -> ndim)
#define hypre_CommInfoSendBoxes(info)      (info -> send_boxes)
#define hypre_CommInfoSendStride(info)     (info -> send_stride)
#define hypre_CommInfoSendProcesses(info)  (info -> send_processes)
#define hypre_CommInfoSendRBoxnums(info)   (info -> send_rboxnums)
#define hypre_CommInfoSendRBoxes(info)     (info -> send_rboxes)

#define hypre_CommInfoRecvBoxes(info)      (info -> recv_boxes)
#define hypre_CommInfoRecvStride(info)     (info -> recv_stride)
#define hypre_CommInfoRecvProcesses(info)  (info -> recv_processes)
#define hypre_CommInfoRecvRBoxnums(info)   (info -> recv_rboxnums)
#define hypre_CommInfoRecvRBoxes(info)     (info -> recv_rboxes)

#define hypre_CommInfoNumTransforms(info)  (info -> num_transforms)
#define hypre_CommInfoCoords(info)         (info -> coords)
#define hypre_CommInfoDirs(info)           (info -> dirs)
#define hypre_CommInfoSendTransforms(info) (info -> send_transforms)
#define hypre_CommInfoRecvTransforms(info) (info -> recv_transforms)

#define hypre_CommInfoBoxesMatch(info)     (info -> boxes_match)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommEntry
 *--------------------------------------------------------------------------*/

#define hypre_CommEntryOffset(entry)       (entry -> offset)
#define hypre_CommEntryDim(entry)          (entry -> dim)
#define hypre_CommEntryLengthArray(entry)  (entry -> length_array)
#define hypre_CommEntryStrideArray(entry)  (entry -> stride_array)
#define hypre_CommEntryIMap(entry)         (entry -> imap)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommBlock
 *--------------------------------------------------------------------------*/

#define hypre_CommBlockBufsize(blk)       (blk -> bufsize)
#define hypre_CommBlockPfxsize(blk)       (blk -> pfxsize)
#define hypre_CommBlockNDim(blk)          (blk -> ndim)
#define hypre_CommBlockNumValues(blk)     (blk -> num_values)
#define hypre_CommBlockNumEntries(blk)    (blk -> num_entries)
#define hypre_CommBlockEntries(blk)       (blk -> entries)
#define hypre_CommBlockEntry(blk, i)     &(blk -> entries[i])
#define hypre_CommBlockIMaps(blk)         (blk -> imaps)
#define hypre_CommBlockIMap(blk, i)      &(blk -> imaps[i*(blk->num_values)])

#define hypre_CommBlockRemBoxnums(blk)    (blk -> rem_boxnums)
#define hypre_CommBlockRemBoxnum(blk, i)  (blk -> rem_boxnums[i])
#define hypre_CommBlockRemBoxes(blk)      (blk -> rem_boxes)
#define hypre_CommBlockRemBox(blk, i)    &(blk -> rem_boxes[i])
#define hypre_CommBlockRemOrders(blk)     (blk -> rem_orders)
#define hypre_CommBlockRemOrder(blk, i)  &(blk -> rem_orders[i*(blk->num_values)])

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommType
 *--------------------------------------------------------------------------*/

#define hypre_CommTypeFirstComm(type)     (type -> first_comm)
#define hypre_CommTypeProc(type)          (type -> proc)
#define hypre_CommTypeBufsize(type)       (type -> bufsize)
#define hypre_CommTypeNDim(type)          (type -> ndim)
#define hypre_CommTypeNumBlocks(type)     (type -> num_blocks)
#define hypre_CommTypeBlocks(type)        (type -> blocks)
#define hypre_CommTypeBlock(type, i)     &(type -> blocks[i])

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommPkg
 *--------------------------------------------------------------------------*/

#define hypre_CommPkgComm(comm_pkg)            (comm_pkg -> comm)

#define hypre_CommPkgNDim(comm_pkg)            (comm_pkg -> ndim)

#define hypre_CommPkgNumSends(comm_pkg)        (comm_pkg -> num_sends)
#define hypre_CommPkgNumRecvs(comm_pkg)        (comm_pkg -> num_recvs)
#define hypre_CommPkgSendTypes(comm_pkg)       (comm_pkg -> send_types)
#define hypre_CommPkgSendType(comm_pkg, i)    &(comm_pkg -> send_types[i])
#define hypre_CommPkgRecvTypes(comm_pkg)       (comm_pkg -> recv_types)
#define hypre_CommPkgRecvType(comm_pkg, i)    &(comm_pkg -> recv_types[i])

#define hypre_CommPkgCopyFromType(comm_pkg)    (comm_pkg -> copy_from_type)
#define hypre_CommPkgCopyToType(comm_pkg)      (comm_pkg -> copy_to_type)

#define hypre_CommPkgNumBlocks(comm_pkg)       (comm_pkg -> num_blocks)
#define hypre_CommPkgRecvStrides(comm_pkg)     (comm_pkg -> recv_strides)
#define hypre_CommPkgRecvDataSpaces(comm_pkg)  (comm_pkg -> recv_data_spaces)
#define hypre_CommPkgRecvDataOffsets(comm_pkg) (comm_pkg -> recv_data_offsets)
#define hypre_CommPkgBoxesMatch(comm_pkg)      (comm_pkg -> boxes_match)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_CommHandle
 *--------------------------------------------------------------------------*/

#define hypre_CommHandleCommPkg(comm_handle)     (comm_handle -> comm_pkg)
#define hypre_CommHandleSendData(comm_handle)    (comm_handle -> send_data)
#define hypre_CommHandleRecvData(comm_handle)    (comm_handle -> recv_data)
#define hypre_CommHandleNumRequests(comm_handle) (comm_handle -> num_requests)
#define hypre_CommHandleRequests(comm_handle)    (comm_handle -> requests)
#define hypre_CommHandleStatus(comm_handle)      (comm_handle -> status)
#define hypre_CommHandleSendBuffers(comm_handle) (comm_handle -> send_buffers)
#define hypre_CommHandleRecvBuffers(comm_handle) (comm_handle -> recv_buffers)
#define hypre_CommHandleAction(comm_handle)      (comm_handle -> action)

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/



/******************************************************************************
 *
 * Header info for computation
 *
 *****************************************************************************/

#ifndef hypre_COMPUTATION_HEADER
#define hypre_COMPUTATION_HEADER

/*--------------------------------------------------------------------------
 * hypre_ComputeInfo:
 *--------------------------------------------------------------------------*/

typedef struct hypre_ComputeInfo_struct
{
   hypre_CommInfo        *comm_info;

   hypre_BoxArrayArray   *indt_boxes;
   hypre_BoxArrayArray   *dept_boxes;
   hypre_Index            stride;

} hypre_ComputeInfo;

/*--------------------------------------------------------------------------
 * hypre_ComputePkg:
 *   Structure containing information for doing computations.
 *--------------------------------------------------------------------------*/

typedef struct hypre_ComputePkg_struct
{
   hypre_CommPkg         *comm_pkg;

   hypre_BoxArrayArray   *indt_boxes;
   hypre_BoxArrayArray   *dept_boxes;
   hypre_Index            stride;

   hypre_StructGrid      *grid;
   HYPRE_Int              num_values;

} hypre_ComputePkg;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_ComputeInfo
 *--------------------------------------------------------------------------*/

#define hypre_ComputeInfoCommInfo(info)     (info -> comm_info)
#define hypre_ComputeInfoIndtBoxes(info)    (info -> indt_boxes)
#define hypre_ComputeInfoDeptBoxes(info)    (info -> dept_boxes)
#define hypre_ComputeInfoStride(info)       (info -> stride)

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_ComputePkg
 *--------------------------------------------------------------------------*/

#define hypre_ComputePkgCommPkg(compute_pkg)      (compute_pkg -> comm_pkg)

#define hypre_ComputePkgIndtBoxes(compute_pkg)    (compute_pkg -> indt_boxes)
#define hypre_ComputePkgDeptBoxes(compute_pkg)    (compute_pkg -> dept_boxes)
#define hypre_ComputePkgStride(compute_pkg)       (compute_pkg -> stride)

#define hypre_ComputePkgGrid(compute_pkg)         (compute_pkg -> grid)
#define hypre_ComputePkgNumValues(compute_pkg)    (compute_pkg -> num_values)

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2014,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

#ifndef hypre_STRUCT_STMATRIX_HEADER
#define hypre_STRUCT_STMATRIX_HEADER

#include <assert.h>

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

typedef struct
{
   HYPRE_Int     id;      /* Stencil matrix id for this term */
   HYPRE_Int     entry;   /* Stencil entry number */
   hypre_Index   shift;   /* Stencil shift from center */

} hypre_StTerm;

typedef struct coeff_link
{
   HYPRE_Int          nterms;  /* Number of terms */
   hypre_StTerm      *terms;   /* Array of terms */

   struct coeff_link *prev;
   struct coeff_link *next;

} hypre_StCoeff;

typedef struct
{
   HYPRE_Int       id;         /* Matrix ID */
   HYPRE_Int       size;       /* Number of stencil entries */

   hypre_Index     rmap;       /* Range map */
   hypre_Index     dmap;       /* Domain map */

   hypre_Index    *shapes;     /* Offsets describing the stencil's shape */
   hypre_StCoeff **coeffs;     /* Description of coefficients */

} hypre_StMatrix;

/*--------------------------------------------------------------------------
 * Accessor macros:
 *--------------------------------------------------------------------------*/

#define hypre_StTermID(term)           ((term) -> id)
#define hypre_StTermEntry(term)        ((term) -> entry)
#define hypre_StTermShift(term)        ((term) -> shift)

#define hypre_StCoeffNTerms(coeff)     ((coeff) -> nterms)
#define hypre_StCoeffTerms(coeff)      ((coeff) -> terms)
#define hypre_StCoeffTerm(coeff, t)   &((coeff) -> terms[t])
#define hypre_StCoeffPrev(coeff)       ((coeff) -> prev)
#define hypre_StCoeffNext(coeff)       ((coeff) -> next)

#define hypre_StMatrixID(stmat)        ((stmat) -> id)
#define hypre_StMatrixSize(stmat)      ((stmat) -> size)
#define hypre_StMatrixRMap(stmat)      ((stmat) -> rmap)
#define hypre_StMatrixDMap(stmat)      ((stmat) -> dmap)
#define hypre_StMatrixShapes(stmat)    ((stmat) -> shapes)
#define hypre_StMatrixOffset(stmat, e) ((stmat) -> shapes[e])
#define hypre_StMatrixCoeffs(stmat)    ((stmat) -> coeffs)
#define hypre_StMatrixCoeff(stmat, e)  ((stmat) -> coeffs[e])

/*--------------------------------------------------------------------------
 * Prototypes:
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_StIndexCopy( hypre_Index index1,
                   hypre_Index index2,
                   HYPRE_Int   ndim );
HYPRE_Int
hypre_StIndexNegate( hypre_Index index,
                     HYPRE_Int   ndim );
HYPRE_Int
hypre_StIndexShift( hypre_Index index,
                    hypre_Index shift,
                    HYPRE_Int   ndim );
HYPRE_Int
hypre_StIndexPrint( hypre_Index index,
                    char        lchar,
                    char        rchar,
                    HYPRE_Int   ndim );
HYPRE_Int
hypre_StTermCopy( hypre_StTerm *term1,
                  hypre_StTerm *term2,
                  HYPRE_Int     ndim );
HYPRE_Int
hypre_StTermPrint( hypre_StTerm *term,
                   char         *matnames,
                   HYPRE_Int     ndim );
HYPRE_Int
hypre_StCoeffCreate( HYPRE_Int       nterms,
                     hypre_StCoeff **coeff_ptr );
HYPRE_Int
hypre_StCoeffClone( hypre_StCoeff  *coeff,
                    HYPRE_Int       ndim,
                    hypre_StCoeff **clone_ptr );
HYPRE_Int
hypre_StCoeffDestroy( hypre_StCoeff *coeff );
HYPRE_Int
hypre_StCoeffShift( hypre_StCoeff *coeff,
                    hypre_Index    shift,
                    HYPRE_Int      ndim );
HYPRE_Int
hypre_StCoeffPush( hypre_StCoeff **stack_ptr,
                   hypre_StCoeff  *coeff );
HYPRE_Int
hypre_StCoeffMult( hypre_StCoeff  *Acoeff,
                   hypre_StCoeff  *Bcoeff,
                   HYPRE_Int       ndim,
                   hypre_StCoeff **Ccoeff_ptr );
HYPRE_Int
hypre_StCoeffPrint( hypre_StCoeff *coeff,
                    char          *matnames,
                    HYPRE_Int      ndim );
HYPRE_Int
hypre_StMatrixCreate( HYPRE_Int        id,
                      HYPRE_Int        size,
                      HYPRE_Int        ndim,
                      hypre_StMatrix **matrix_ptr );
HYPRE_Int
hypre_StMatrixClone( hypre_StMatrix  *matrix,
                     HYPRE_Int        ndim,
                     hypre_StMatrix **mclone_ptr );
HYPRE_Int
hypre_StMatrixDestroy( hypre_StMatrix *matrix );
HYPRE_Int
hypre_StMatrixTranspose( hypre_StMatrix *matrix,
                         HYPRE_Int       ndim );
HYPRE_Int
hypre_StMatrixMatmat( hypre_StMatrix  *A,
                      hypre_StMatrix  *B,
                      HYPRE_Int        Cid,
                      HYPRE_Int        ndim,
                      hypre_StMatrix **C_ptr );
HYPRE_Int
hypre_StMatrixMatmult( HYPRE_Int        nmatrices,
                       hypre_StMatrix **matrices,
                       HYPRE_Int       *transposes,
                       HYPRE_Int        Cid,
                       HYPRE_Int        ndim,
                       hypre_StMatrix **C_ptr );
HYPRE_Int
hypre_StMatrixPrint( hypre_StMatrix *matrix,
                     char           *matnames,
                     HYPRE_Int       ndim );

HYPRE_Int
hypre_StMatrixNEntryCoeffs( hypre_StMatrix *matrix,
                            HYPRE_Int       entry );

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for the hypre_StructMatrix structures
 *
 *****************************************************************************/

#ifndef hypre_STRUCT_MATRIX_HEADER
#define hypre_STRUCT_MATRIX_HEADER

#include <assert.h>

/*--------------------------------------------------------------------------
 * hypre_StructMatrix:
 *
 * Rectangular matrices have different range and domain grids, which are defined
 * in terms of a common base grid and index space.  The range grid consists of a
 * coarsened subset of boxes in the base grid, as specified by the box numbers
 * in 'ran_boxnums' and the coarsening factor 'ran_stride'.  The domain grid is
 * similarly defined via 'dom_boxnums' and 'dom_stride'.  Either the range index
 * space is a coarsening of the domain index space or vice-versa.  The data
 * storage is dictated by the coarsest grid as indicated (for convenience) by
 * the two booleans 'range_is_coarse' and 'domain_is_coarse'.  The stencil
 * always represents a "row" stencil that operates on the domain grid and
 * produces a value on the range grid.  The data interface and accessor macros
 * are also row-stencil based, regardless of the underlying storage.  Each
 * stencil entry can have either constant or variable coefficients as indicated
 * by the stencil-sized array 'constant'.
 *
 * The 'data' pointer below has space at the beginning for constant stencil
 * coefficient values followed by the stored variable coefficient values.
 * Accessing coefficients is done via 'data_indices' through the interface
 * routine hypre_StructMatrixBoxData().  The number of boxes in data_boxes,
 * data_space, and data_indices is the same as in the base grid, even though
 * both ran_nboxes and dom_nboxes may be smaller.
 *
 * The 'num_ghost' and 'sym_ghost' arrays are used to determine how many ghost
 * layers of storage to keep.  They determine the dimensions of 'data_space' and
 * 'data_boxes', but they do not imply communication of any sort.  That is, the
 * values stored in the ghost layers will not be correct without triggering some
 * additional communication either explicitly or by setting the 'symmetric' or
 * 'transpose' flags.
 *--------------------------------------------------------------------------*/

typedef struct hypre_StructMatrix_struct
{
   MPI_Comm              comm;

   hypre_StructGrid     *grid;          /* Base grid */
   HYPRE_Int             ran_ghsize;    /* Number of vars in range grid including ghosts */
   HYPRE_Int             ran_nboxes;    /* Range grid number of boxes */
   HYPRE_Int            *ran_boxnums;   /* Range grid boxnums in base grid */
   hypre_Index           ran_stride;    /* Range grid coarsening stride */
   HYPRE_Int             dom_ghsize;    /* Number of vars in domain grid including ghosts */
   HYPRE_Int             dom_nboxes;    /* Domain grid number of boxes */
   HYPRE_Int            *dom_boxnums;   /* Domain grid boxnums in base grid */
   hypre_Index           dom_stride;    /* Domain grid coarsening stride */

   hypre_StructStencil  *user_stencil;
   hypre_StructStencil  *stencil;
   HYPRE_Int            *constant;      /* Which stencil entries are constant? */

   HYPRE_Complex        *data;          /* Pointer to matrix data */
   hypre_BoxArray       *data_space;    /* Layout of data (coarse index space) */
   hypre_BoxArray       *data_boxes;    /* Data extents on fine index space */
   HYPRE_Int             data_alloced;  /* Boolean used for freeing data */
   HYPRE_Int             data_size;     /* Size of matrix data */
   HYPRE_Int           **data_indices;  /* Array of indices into the data array.
                                           data_indices[b][s] is the starting
                                           index of data for boxnum b and
                                           stencil coefficient s */
   HYPRE_Int            *const_indices; /* Indices into the data array for constant data */
   HYPRE_Int             vdata_offset;  /* Offset to variable-coeff matrix data */
   HYPRE_Int             num_values;    /* Number of "stored" variable coeffs */
   HYPRE_Int             num_cvalues;   /* Number of "stored" constant coeffs */
   HYPRE_Int             range_is_coarse;   /* 1 -> the range is coarse */
   HYPRE_Int             domain_is_coarse;  /* 1 -> the domain is coarse */
   HYPRE_Int             constant_coefficient;  /* RDF: Phase this out in favor
                                                   of 'constant' array above.
                                                   Values can be {0, 1, 2} ->
                                                   {variable, constant, constant
                                                   with variable diagonal} */
   HYPRE_Int             symmetric;      /* Is the matrix symmetric */
   HYPRE_Int            *symm_entries;   /* Which entries are "symmetric" */
   HYPRE_Int             transpose;      /* Transpose stored also? */
   HYPRE_Int             num_ghost[2*HYPRE_MAXDIM]; /* Min num ghost layers */
   HYPRE_Int             sym_ghost[2*HYPRE_MAXDIM]; /* Ghost layers for symmetric */
   HYPRE_Int             trn_ghost[2*HYPRE_MAXDIM]; /* Ghost layers for transpose */

   HYPRE_Int             global_size;  /* Total number of nonzero coeffs */

   HYPRE_Int             ref_count;

   /* Information needed to Restore() after Resize() */
   HYPRE_Complex        *save_data;
   hypre_BoxArray       *save_data_space;
   HYPRE_Int             save_data_size;

} hypre_StructMatrix;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_StructMatrix
 *--------------------------------------------------------------------------*/

#define hypre_StructMatrixComm(matrix)          ((matrix) -> comm)
#define hypre_StructMatrixGrid(matrix)          ((matrix) -> grid)
#define hypre_StructMatrixRanGhsize(matrix)     ((matrix) -> ran_ghsize)
#define hypre_StructMatrixRanNBoxes(matrix)     ((matrix) -> ran_nboxes)
#define hypre_StructMatrixRanBoxnums(matrix)    ((matrix) -> ran_boxnums)
#define hypre_StructMatrixRanBoxnum(matrix, i)  ((matrix) -> ran_boxnums[i])
#define hypre_StructMatrixRanStride(matrix)     ((matrix) -> ran_stride)
#define hypre_StructMatrixDomGhsize(matrix)     ((matrix) -> dom_ghsize)
#define hypre_StructMatrixDomNBoxes(matrix)     ((matrix) -> dom_nboxes)
#define hypre_StructMatrixDomBoxnums(matrix)    ((matrix) -> dom_boxnums)
#define hypre_StructMatrixDomBoxnum(matrix, i)  ((matrix) -> dom_boxnums[i])
#define hypre_StructMatrixDomStride(matrix)     ((matrix) -> dom_stride)
#define hypre_StructMatrixUserStencil(matrix)   ((matrix) -> user_stencil)
#define hypre_StructMatrixStencil(matrix)       ((matrix) -> stencil)
#define hypre_StructMatrixConstant(matrix)      ((matrix) -> constant)
#define hypre_StructMatrixConstEntry(matrix, s) ((matrix) -> constant[s])
#define hypre_StructMatrixData(matrix)          ((matrix) -> data)
#define hypre_StructMatrixDataSpace(matrix)     ((matrix) -> data_space)
#define hypre_StructMatrixDataBoxes(matrix)     ((matrix) -> data_boxes)
#define hypre_StructMatrixDataAlloced(matrix)   ((matrix) -> data_alloced)
#define hypre_StructMatrixDataSize(matrix)      ((matrix) -> data_size)
#define hypre_StructMatrixDataIndices(matrix)   ((matrix) -> data_indices)
#define hypre_StructMatrixConstIndices(matrix)  ((matrix) -> const_indices)
#define hypre_StructMatrixVDataOffset(matrix)   ((matrix) -> vdata_offset)
#define hypre_StructMatrixNumValues(matrix)     ((matrix) -> num_values)
#define hypre_StructMatrixNumCValues(matrix)    ((matrix) -> num_cvalues)
#define hypre_StructMatrixRangeIsCoarse(matrix) ((matrix) -> range_is_coarse)
#define hypre_StructMatrixDomainIsCoarse(matrix)((matrix) -> domain_is_coarse)
#define hypre_StructMatrixConstantCoefficient(matrix) ((matrix) -> constant_coefficient)
#define hypre_StructMatrixSymmetric(matrix)     ((matrix) -> symmetric)
#define hypre_StructMatrixSymmEntries(matrix)   ((matrix) -> symm_entries)
#define hypre_StructMatrixTranspose(matrix)     ((matrix) -> transpose)
#define hypre_StructMatrixNumGhost(matrix)      ((matrix) -> num_ghost)
#define hypre_StructMatrixSymGhost(matrix)      ((matrix) -> sym_ghost)
#define hypre_StructMatrixTrnGhost(matrix)      ((matrix) -> trn_ghost)
#define hypre_StructMatrixGlobalSize(matrix)    ((matrix) -> global_size)
#define hypre_StructMatrixRefCount(matrix)      ((matrix) -> ref_count)

#define hypre_StructMatrixSaveData(matrix)      ((matrix) -> save_data)
#define hypre_StructMatrixSaveDataSpace(matrix) ((matrix) -> save_data_space)
#define hypre_StructMatrixSaveDataSize(matrix)  ((matrix) -> save_data_size)

#define hypre_StructMatrixNDim(matrix) \
hypre_StructGridNDim(hypre_StructMatrixGrid(matrix))

#define hypre_StructMatrixVData(matrix) \
(hypre_StructMatrixData(matrix) + hypre_StructMatrixVDataOffset(matrix))

#define hypre_StructMatrixBoxData(matrix, b, s) \
(hypre_StructMatrixData(matrix) + hypre_StructMatrixDataIndices(matrix)[b][s])

#define hypre_StructMatrixConstData(matrix, s) \
(hypre_StructMatrixData(matrix) + hypre_StructMatrixConstIndices(matrix)[s])

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/******************************************************************************
 *
 * Header info for the hypre_StructVector structures
 *
 *****************************************************************************/

#ifndef hypre_STRUCT_VECTOR_HEADER
#define hypre_STRUCT_VECTOR_HEADER

/*--------------------------------------------------------------------------
 * hypre_StructVector:
 *
 * Most of the routines currently only work when the base grid and grid are the
 * same (i.e., when nboxes equals the number of boxes in the grid and stride is
 * the unit stride).  The number of boxes in data_space and data_indices is the
 * same as in the base grid, even though nboxes may be smaller.
 *--------------------------------------------------------------------------*/

typedef struct hypre_StructVector_struct
{
   MPI_Comm              comm;

   hypre_StructGrid     *grid;         /* Base grid */
   HYPRE_Int             nboxes;       /* Grid number of boxes */
   HYPRE_Int            *boxnums;      /* Grid boxnums in base grid */
   hypre_Index           stride;       /* Grid coarsening stride */

   HYPRE_Complex        *data;         /* Pointer to vector data */
   hypre_BoxArray       *data_space;   /* Layout of vector data */
   HYPRE_Int             data_alloced; /* Boolean used for freeing data */
   HYPRE_Int             data_size;    /* Size of vector data */
   HYPRE_Int            *data_indices; /* Array of indices into the data array.
                                          data_indices[b] is the starting index
                                          of data corresponding to boxnum b. */

   HYPRE_Int             num_ghost[2*HYPRE_MAXDIM]; /* Num ghost layers in each
                                                     * direction */
   HYPRE_Int             bghost_not_clear; /* Are boundary ghosts clear? */

   HYPRE_Int             global_size;  /* Total number coefficients */

   HYPRE_Int             ref_count;

   /* Information needed to Restore() after Reindex() and Resize() */
   hypre_StructGrid     *save_grid;
   hypre_Index           save_stride;
   HYPRE_Complex        *save_data;
   hypre_BoxArray       *save_data_space;
   HYPRE_Int             save_data_size;

} hypre_StructVector;

/*--------------------------------------------------------------------------
 * Accessor macros: hypre_StructVector
 *--------------------------------------------------------------------------*/

#define hypre_StructVectorComm(vector)          ((vector) -> comm)
#define hypre_StructVectorGrid(vector)          ((vector) -> grid)
#define hypre_StructVectorNBoxes(vector)        ((vector) -> nboxes)
#define hypre_StructVectorBoxnums(vector)       ((vector) -> boxnums)
#define hypre_StructVectorBoxnum(vector, i)     ((vector) -> boxnums[i])
#define hypre_StructVectorStride(vector)        ((vector) -> stride)
#define hypre_StructVectorData(vector)          ((vector) -> data)
#define hypre_StructVectorDataSpace(vector)     ((vector) -> data_space)
#define hypre_StructVectorDataAlloced(vector)   ((vector) -> data_alloced)
#define hypre_StructVectorDataSize(vector)      ((vector) -> data_size)
#define hypre_StructVectorDataIndices(vector)   ((vector) -> data_indices)
#define hypre_StructVectorNumGhost(vector)      ((vector) -> num_ghost)
#define hypre_StructVectorBGhostNotClear(vector)((vector) -> bghost_not_clear)
#define hypre_StructVectorGlobalSize(vector)    ((vector) -> global_size)
#define hypre_StructVectorRefCount(vector)      ((vector) -> ref_count)

#define hypre_StructVectorSaveGrid(vector)      ((vector) -> save_grid)
#define hypre_StructVectorSaveStride(vector)    ((vector) -> save_stride)
#define hypre_StructVectorSaveData(vector)      ((vector) -> save_data)
#define hypre_StructVectorSaveDataSpace(vector) ((vector) -> save_data_space)
#define hypre_StructVectorSaveDataSize(vector)  ((vector) -> save_data_size)

#define hypre_StructVectorNDim(vector) \
hypre_StructGridNDim(hypre_StructVectorGrid(vector))

#define hypre_StructVectorBox(vector, b) \
hypre_BoxArrayBox(hypre_StructVectorDataSpace(vector), b)

#define hypre_StructVectorBoxData(vector, b) \
(hypre_StructVectorData(vector) + hypre_StructVectorDataIndices(vector)[b])

#define hypre_StructVectorBoxDataValue(vector, b, index) \
(hypre_StructVectorBoxData(vector, b) + \
 hypre_BoxIndexRank(hypre_StructVectorBox(vector, b), index))

#endif
/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/

/* assumed_part.c */
HYPRE_Int hypre_APSubdivideRegion ( hypre_Box *region , HYPRE_Int dim , HYPRE_Int level , hypre_BoxArray *box_array , HYPRE_Int *num_new_boxes );
HYPRE_Int hypre_APFindMyBoxesInRegions ( hypre_BoxArray *region_array , hypre_BoxArray *my_box_array , HYPRE_Int **p_count_array , HYPRE_Real **p_vol_array );
HYPRE_Int hypre_APGetAllBoxesInRegions ( hypre_BoxArray *region_array , hypre_BoxArray *my_box_array , HYPRE_Int **p_count_array , HYPRE_Real **p_vol_array , MPI_Comm comm );
HYPRE_Int hypre_APShrinkRegions ( hypre_BoxArray *region_array , hypre_BoxArray *my_box_array , MPI_Comm comm );
HYPRE_Int hypre_APPruneRegions ( hypre_BoxArray *region_array , HYPRE_Int **p_count_array , HYPRE_Real **p_vol_array );
HYPRE_Int hypre_APRefineRegionsByVol ( hypre_BoxArray *region_array , HYPRE_Real *vol_array , HYPRE_Int max_regions , HYPRE_Real gamma , HYPRE_Int dim , HYPRE_Int *return_code , MPI_Comm comm );
HYPRE_Int hypre_StructAssumedPartitionCreate ( HYPRE_Int dim , hypre_Box *bounding_box , HYPRE_Real global_boxes_size , HYPRE_Int global_num_boxes , hypre_BoxArray *local_boxes , HYPRE_Int max_regions , HYPRE_Int max_refinements , HYPRE_Real gamma , MPI_Comm comm , hypre_StructAssumedPart **p_assumed_partition );
HYPRE_Int hypre_StructAssumedPartitionDestroy ( hypre_StructAssumedPart *assumed_part );
HYPRE_Int hypre_APFillResponseStructAssumedPart ( void *p_recv_contact_buf , HYPRE_Int contact_size , HYPRE_Int contact_proc , void *ro , MPI_Comm comm , void **p_send_response_buf , HYPRE_Int *response_message_size );
HYPRE_Int hypre_StructAssumedPartitionGetRegionsFromProc ( hypre_StructAssumedPart *assumed_part , HYPRE_Int proc_id , hypre_BoxArray *assumed_regions );
HYPRE_Int hypre_StructAssumedPartitionGetProcsFromBox ( hypre_StructAssumedPart *assumed_part , hypre_Box *box , HYPRE_Int *num_proc_array , HYPRE_Int *size_alloc_proc_array , HYPRE_Int **p_proc_array );
HYPRE_Int hypre_StructAssumedPartitionPrint ( const char *filename , hypre_StructAssumedPart *ap );
HYPRE_Int hypre_StructCoarsenAP ( hypre_StructAssumedPart *ap , hypre_Index origin , hypre_Index stride , hypre_StructAssumedPart **new_ap_ptr );

/* box_algebra.c */
HYPRE_Int hypre_IntersectBoxes ( hypre_Box *box1 , hypre_Box *box2 , hypre_Box *ibox );
HYPRE_Int hypre_SubtractBoxes ( hypre_Box *box1 , hypre_Box *box2 , hypre_BoxArray *box_array );
HYPRE_Int hypre_SubtractBoxArrays ( hypre_BoxArray *box_array1 , hypre_BoxArray *box_array2 , hypre_BoxArray *tmp_box_array );
HYPRE_Int hypre_UnionBoxes ( hypre_BoxArray *boxes );
HYPRE_Int hypre_MinUnionBoxes ( hypre_BoxArray *boxes );

/* box_boundary.c */
HYPRE_Int hypre_BoxBoundaryIntersect ( hypre_Box *box , hypre_StructGrid *grid , HYPRE_Int d , HYPRE_Int dir , hypre_BoxArray *boundary );
HYPRE_Int hypre_BoxBoundaryG ( hypre_Box *box , hypre_StructGrid *g , hypre_BoxArray *boundary );
HYPRE_Int hypre_BoxBoundaryDG ( hypre_Box *box , hypre_StructGrid *g , hypre_BoxArray *boundarym , hypre_BoxArray *boundaryp , HYPRE_Int d );
HYPRE_Int hypre_GeneralBoxBoundaryIntersect( hypre_Box *box, hypre_StructGrid *grid, hypre_Index stencil_offset, hypre_BoxArray *boundary );

/* box.c */
HYPRE_Int hypre_SetIndex ( hypre_Index index , HYPRE_Int val );
HYPRE_Int hypre_CopyIndex( hypre_Index in_index , hypre_Index out_index );
HYPRE_Int hypre_CopyToIndex( hypre_Index in_index , HYPRE_Int ndim , hypre_Index out_index );
HYPRE_Int hypre_CopyToCleanIndex( hypre_Index in_index , HYPRE_Int ndim , hypre_Index out_index );
HYPRE_Int hypre_IndexEqual ( hypre_Index index , HYPRE_Int val , HYPRE_Int ndim );
HYPRE_Int hypre_IndexMin( hypre_Index index , HYPRE_Int ndim );
HYPRE_Int hypre_IndexMax( hypre_Index index , HYPRE_Int ndim );
HYPRE_Int hypre_AddIndexes ( hypre_Index index1 , hypre_Index index2 , HYPRE_Int ndim , hypre_Index result );
HYPRE_Int hypre_SubtractIndexes ( hypre_Index index1 , hypre_Index index2 , HYPRE_Int ndim , hypre_Index result );
HYPRE_Int hypre_IndexesEqual ( hypre_Index index1 , hypre_Index index2 , HYPRE_Int ndim );
hypre_Box *hypre_BoxCreate ( HYPRE_Int ndim );
HYPRE_Int hypre_BoxDestroy ( hypre_Box *box );
HYPRE_Int hypre_BoxInit( hypre_Box *box , HYPRE_Int  ndim );
HYPRE_Int hypre_BoxSetExtents ( hypre_Box *box , hypre_Index imin , hypre_Index imax );
HYPRE_Int hypre_CopyBox( hypre_Box *box1 , hypre_Box *box2 );
hypre_Box *hypre_BoxClone ( hypre_Box *box );
HYPRE_Int hypre_BoxVolume( hypre_Box *box );
HYPRE_Real hypre_doubleBoxVolume( hypre_Box *box );
HYPRE_Int hypre_BoxStrideVolume ( hypre_Box *box , hypre_Index stride );
HYPRE_Int hypre_BoxPartialVolume( hypre_Box *box, hypre_Index partial_volume);
HYPRE_Int hypre_BoxNnodes( hypre_Box *box );
HYPRE_Int hypre_IndexInBox ( hypre_Index index , hypre_Box *box );
HYPRE_Int hypre_BoxMaxSize( hypre_Box *box );
HYPRE_Int hypre_BoxGetSize ( hypre_Box *box , hypre_Index size );
HYPRE_Int hypre_BoxGetStrideSize ( hypre_Box *box , hypre_Index stride , hypre_Index size );
HYPRE_Int hypre_BoxGetStrideVolume ( hypre_Box *box , hypre_Index stride , HYPRE_Int *volume_ptr );
HYPRE_Int hypre_BoxIndexRank( hypre_Box *box , hypre_Index index );
HYPRE_Int hypre_BoxRankIndex( hypre_Box *box , HYPRE_Int rank , hypre_Index index );
HYPRE_Int hypre_BoxOffsetDistance( hypre_Box *box , hypre_Index index );
HYPRE_Int hypre_BoxShiftPos( hypre_Box *box , hypre_Index shift );
HYPRE_Int hypre_BoxShiftNeg( hypre_Box *box , hypre_Index shift );
HYPRE_Int hypre_BoxGrowByIndex( hypre_Box *box , hypre_Index  index );
HYPRE_Int hypre_BoxGrowByValue( hypre_Box *box , HYPRE_Int val );
HYPRE_Int hypre_BoxGrowByBox( hypre_Box *box , hypre_Box *gbox );
HYPRE_Int hypre_BoxGrowByArray ( hypre_Box *box , HYPRE_Int *array );
hypre_BoxArray *hypre_BoxArrayCreate ( HYPRE_Int size , HYPRE_Int ndim );
HYPRE_Int hypre_BoxArrayDestroy ( hypre_BoxArray *box_array );
HYPRE_Int hypre_BoxArraySetSize ( hypre_BoxArray *box_array , HYPRE_Int size );
hypre_BoxArray *hypre_BoxArrayClone ( hypre_BoxArray *box_array );
HYPRE_Int hypre_AppendBox ( hypre_Box *box , hypre_BoxArray *box_array );
HYPRE_Int hypre_DeleteBox ( hypre_BoxArray *box_array , HYPRE_Int index );
HYPRE_Int hypre_DeleteMultipleBoxes ( hypre_BoxArray *box_array , HYPRE_Int *indices , HYPRE_Int num );
HYPRE_Int hypre_AppendBoxArray ( hypre_BoxArray *box_array_0 , hypre_BoxArray *box_array_1 );
hypre_BoxArrayArray *hypre_BoxArrayArrayCreate ( HYPRE_Int size , HYPRE_Int ndim );
HYPRE_Int hypre_BoxArrayArrayDestroy ( hypre_BoxArrayArray *box_array_array );
hypre_BoxArrayArray *hypre_BoxArrayArrayClone ( hypre_BoxArrayArray *box_array_array );

/* box_manager.c */
HYPRE_Int hypre_BoxManEntryGetInfo ( hypre_BoxManEntry *entry , void **info_ptr );
HYPRE_Int hypre_BoxManEntryGetExtents ( hypre_BoxManEntry *entry , hypre_Index imin , hypre_Index imax );
HYPRE_Int hypre_BoxManEntryGetStride ( hypre_BoxManEntry *entry , hypre_Index stride );
HYPRE_Int hypre_BoxManEntryCopy ( hypre_BoxManEntry *fromentry , hypre_BoxManEntry *toentry );
HYPRE_Int hypre_BoxManSetAllGlobalKnown ( hypre_BoxManager *manager , HYPRE_Int known );
HYPRE_Int hypre_BoxManGetAllGlobalKnown ( hypre_BoxManager *manager , HYPRE_Int *known );
HYPRE_Int hypre_BoxManSetIsEntriesSort ( hypre_BoxManager *manager , HYPRE_Int is_sort );
HYPRE_Int hypre_BoxManGetIsEntriesSort ( hypre_BoxManager *manager , HYPRE_Int *is_sort );
HYPRE_Int hypre_BoxManGetGlobalIsGatherCalled ( hypre_BoxManager *manager , MPI_Comm comm , HYPRE_Int *is_gather );
HYPRE_Int hypre_BoxManGetAssumedPartition ( hypre_BoxManager *manager , hypre_StructAssumedPart **assumed_partition );
HYPRE_Int hypre_BoxManSetAssumedPartition ( hypre_BoxManager *manager , hypre_StructAssumedPart *assumed_partition );
HYPRE_Int hypre_BoxManSetBoundingBox ( hypre_BoxManager *manager , hypre_Box *bounding_box );
HYPRE_Int hypre_BoxManSetNumGhost ( hypre_BoxManager *manager , HYPRE_Int *num_ghost );
HYPRE_Int hypre_BoxManDeleteMultipleEntriesAndInfo ( hypre_BoxManager *manager , HYPRE_Int *indices , HYPRE_Int num );
HYPRE_Int hypre_BoxManCreate ( HYPRE_Int max_nentries , HYPRE_Int info_size , HYPRE_Int dim , hypre_Box *bounding_box , MPI_Comm comm , hypre_BoxManager **manager_ptr );
HYPRE_Int hypre_BoxManIncSize ( hypre_BoxManager *manager , HYPRE_Int inc_size );
HYPRE_Int hypre_BoxManDestroy ( hypre_BoxManager *manager );
HYPRE_Int hypre_BoxManAddEntry ( hypre_BoxManager *manager , hypre_Index imin , hypre_Index imax , HYPRE_Int proc_id , HYPRE_Int box_id , void *info );
HYPRE_Int hypre_BoxManGetEntry ( hypre_BoxManager *manager , HYPRE_Int proc , HYPRE_Int id , hypre_BoxManEntry **entry_ptr );
HYPRE_Int hypre_BoxManGetAllEntries ( hypre_BoxManager *manager , HYPRE_Int *num_entries , hypre_BoxManEntry **entries );
HYPRE_Int hypre_BoxManGetAllEntriesBoxes ( hypre_BoxManager *manager , hypre_BoxArray *boxes );
HYPRE_Int hypre_BoxManGetLocalEntriesBoxes ( hypre_BoxManager *manager , hypre_BoxArray *boxes );
HYPRE_Int hypre_BoxManGetAllEntriesBoxesProc ( hypre_BoxManager *manager , hypre_BoxArray *boxes , HYPRE_Int **procs_ptr );
HYPRE_Int hypre_BoxManGatherEntries ( hypre_BoxManager *manager , hypre_Index imin , hypre_Index imax );
HYPRE_Int hypre_BoxManAssemble ( hypre_BoxManager *manager );
HYPRE_Int hypre_BoxManIntersect ( hypre_BoxManager *manager , hypre_Index ilower , hypre_Index iupper , hypre_BoxManEntry ***entries_ptr , HYPRE_Int *nentries_ptr );
HYPRE_Int hypre_FillResponseBoxManAssemble1 ( void *p_recv_contact_buf , HYPRE_Int contact_size , HYPRE_Int contact_proc , void *ro , MPI_Comm comm , void **p_send_response_buf , HYPRE_Int *response_message_size );
HYPRE_Int hypre_FillResponseBoxManAssemble2 ( void *p_recv_contact_buf , HYPRE_Int contact_size , HYPRE_Int contact_proc , void *ro , MPI_Comm comm , void **p_send_response_buf , HYPRE_Int *response_message_size );

/* coarsen.c */
HYPRE_Int hypre_MapToCoarseIndex ( hypre_Index index , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_MapToFineIndex ( hypre_Index index , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_StructMapFineToCoarse ( hypre_Index findex , hypre_Index origin , hypre_Index stride , hypre_Index cindex );
HYPRE_Int hypre_StructMapCoarseToFine ( hypre_Index cindex , hypre_Index origin , hypre_Index stride , hypre_Index findex );
HYPRE_Int
hypre_ComputeCoarseOriginStride ( hypre_Index coarse_origin , hypre_Index coarse_stride , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_CoarsenBox ( hypre_Box *box , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_AdaptiveCoarsenBox ( hypre_Box *box , hypre_Box *refbox , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_CoarsenPosBox ( hypre_Box *box , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_CoarsenNegBox ( hypre_Box *box , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_RefineBox ( hypre_Box *box , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_CoarsenBoxArray ( hypre_BoxArray *box_array , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_CoarsenBoxArrayArray ( hypre_BoxArrayArray *box_array_array , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_CoarsenUpdateBoxArrayArray ( hypre_BoxArrayArray *boxaa , hypre_IndexRef origin , hypre_Index stride , hypre_BoxArrayArray **new_boxaa_ptr );
HYPRE_Int hypre_CoarsenPosBoxArrayArray ( hypre_BoxArrayArray *boxaa , hypre_IndexRef origin , hypre_Index stride , hypre_BoxArrayArray **new_boxaa_ptr );
HYPRE_Int hypre_CoarsenNegBoxArrayArray ( hypre_BoxArrayArray *boxaa , hypre_IndexRef origin , hypre_Index stride , hypre_BoxArrayArray **new_boxaa_ptr );
HYPRE_Int hypre_AdaptiveCoarsenBoxArrayArray ( hypre_BoxArrayArray *boxaa , hypre_BoxArray *refboxa , hypre_IndexRef origin , hypre_Index stride , hypre_BoxArrayArray **new_boxaa_ptr );
HYPRE_Int hypre_StructCoarsen ( hypre_StructGrid *fgrid , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int prune , hypre_StructGrid **cgrid_ptr );

/* communication_info.c */
hypre_CommStencil *hypre_CommStencilCreate ( HYPRE_Int  ndim );
HYPRE_Int hypre_CommStencilSetEntry ( hypre_CommStencil *comm_stencil , hypre_Index offset );
HYPRE_Int hypre_CommStencilDestroy ( hypre_CommStencil *comm_stencil );
HYPRE_Int hypre_CommStencilCreateNumGhost ( hypre_CommStencil *comm_stencil , HYPRE_Int **num_ghost_ptr );
HYPRE_Int hypre_CommInfoCreate ( hypre_BoxArrayArray *send_boxes , hypre_BoxArrayArray *recv_boxes , HYPRE_Int **send_procs , HYPRE_Int **recv_procs , HYPRE_Int **send_rboxnums , HYPRE_Int **recv_rboxnums , hypre_BoxArrayArray *send_rboxes , hypre_BoxArrayArray *recv_rboxes , HYPRE_Int boxes_match , hypre_CommInfo **comm_info_ptr );
HYPRE_Int hypre_CommInfoSetTransforms ( hypre_CommInfo *comm_info , HYPRE_Int num_transforms , hypre_Index *coords , hypre_Index *dirs , HYPRE_Int **send_transforms , HYPRE_Int **recv_transforms );
HYPRE_Int hypre_CommInfoGetTransforms ( hypre_CommInfo *comm_info , HYPRE_Int *num_transforms , hypre_Index **coords , hypre_Index **dirs );
HYPRE_Int hypre_CommInfoProjectSend ( hypre_CommInfo *comm_info , hypre_Index index , hypre_Index stride );
HYPRE_Int hypre_CommInfoProjectRecv ( hypre_CommInfo *comm_info , hypre_Index index , hypre_Index stride );
HYPRE_Int hypre_CommInfoDestroy ( hypre_CommInfo *comm_info );
HYPRE_Int hypre_CommInfoClone( hypre_CommInfo *comm_info , hypre_CommInfo **clone_ptr );
HYPRE_Int hypre_CreateCommInfo ( hypre_StructGrid *grid , hypre_CommStencil *comm_stencil , hypre_CommInfo **comm_info_ptr );
HYPRE_Int hypre_CreateCommInfoFromStencil ( hypre_StructGrid *grid , hypre_StructStencil *stencil , hypre_CommInfo **comm_info_ptr );
HYPRE_Int hypre_CreateCommInfoFromNumGhost ( hypre_StructGrid *grid , HYPRE_Int *num_ghost , hypre_CommInfo **comm_info_ptr );
HYPRE_Int hypre_CreateCommInfoFromGrids ( hypre_StructGrid *from_grid , hypre_StructGrid *to_grid , hypre_CommInfo **comm_info_ptr );

/* computation.c */
HYPRE_Int hypre_ComputeInfoCreate ( hypre_CommInfo *comm_info , hypre_BoxArrayArray *indt_boxes , hypre_BoxArrayArray *dept_boxes , hypre_ComputeInfo **compute_info_ptr );
HYPRE_Int hypre_ComputeInfoProjectSend ( hypre_ComputeInfo *compute_info , hypre_Index index , hypre_Index stride );
HYPRE_Int hypre_ComputeInfoProjectRecv ( hypre_ComputeInfo *compute_info , hypre_Index index , hypre_Index stride );
HYPRE_Int hypre_ComputeInfoProjectComp ( hypre_ComputeInfo *compute_info , hypre_Index index , hypre_Index stride );
HYPRE_Int hypre_ComputeInfoDestroy ( hypre_ComputeInfo *compute_info );
HYPRE_Int hypre_CreateComputeInfo ( hypre_StructGrid *grid , hypre_StructStencil *stencil , hypre_ComputeInfo **compute_info_ptr );
HYPRE_Int hypre_ComputePkgCreate ( hypre_ComputeInfo *compute_info , hypre_BoxArray *data_space , HYPRE_Int num_values , hypre_StructGrid *grid , hypre_ComputePkg **compute_pkg_ptr );
HYPRE_Int hypre_ComputePkgDestroy ( hypre_ComputePkg *compute_pkg );
HYPRE_Int hypre_InitializeIndtComputations ( hypre_ComputePkg *compute_pkg , HYPRE_Complex *data , hypre_CommHandle **comm_handle_ptr );
HYPRE_Int hypre_FinalizeIndtComputations ( hypre_CommHandle *comm_handle );

/* project.c */
HYPRE_Int hypre_SnapIndexPos( hypre_Index index , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_SnapIndexNeg( hypre_Index index , hypre_IndexRef origin , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_ConvertToCanonicalIndex( hypre_Index index , hypre_Index stride , HYPRE_Int ndim );
HYPRE_Int hypre_ProjectBox ( hypre_Box *box , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_ProjectBoxArray ( hypre_BoxArray *box_array , hypre_IndexRef origin , hypre_Index stride );
HYPRE_Int hypre_ProjectBoxArrayArray ( hypre_BoxArrayArray *box_array_array , hypre_IndexRef origin , hypre_Index stride );

/* struct_axpy.c */
HYPRE_Int hypre_StructAxpy ( HYPRE_Complex alpha , hypre_StructVector *x , hypre_StructVector *y );

/* struct_communication.c */
HYPRE_Int hypre_CommPkgCreate ( hypre_CommInfo *comm_info , hypre_BoxArray *send_data_space , hypre_BoxArray *recv_data_space , HYPRE_Int num_values , HYPRE_Int **orders , HYPRE_Int reverse , MPI_Comm comm , hypre_CommPkg **comm_pkg_ptr );
HYPRE_Int hypre_CommBlockSetEntries ( hypre_CommBlock *comm_block , HYPRE_Int *boxnums , hypre_Box *boxes , HYPRE_Int *orders , hypre_Index stride , hypre_BoxArray *data_space , HYPRE_Int *data_offsets );
HYPRE_Int hypre_CommBlockSetEntry ( hypre_CommBlock *comm_block , HYPRE_Int comm_num , hypre_Box *box , hypre_Index stride , hypre_Index coord , hypre_Index dir , HYPRE_Int *order , HYPRE_Int *rem_order , hypre_Box *data_box , HYPRE_Int data_box_offset );
HYPRE_Int hypre_CommPkgSetPrefixSizes ( hypre_CommPkg  *comm_pkg );
HYPRE_Int hypre_CommPkgAgglomerate ( HYPRE_Int num_comm_pkgs , hypre_CommPkg **comm_pkgs , hypre_CommPkg **agg_comm_pkg_ptr );
HYPRE_Int hypre_InitializeCommunication ( hypre_CommPkg *comm_pkg , HYPRE_Complex **send_data , HYPRE_Complex **recv_data , HYPRE_Int action , HYPRE_Int tag , hypre_CommHandle **comm_handle_ptr );
HYPRE_Int hypre_FinalizeCommunication ( hypre_CommHandle *comm_handle );
HYPRE_Int hypre_ExchangeLocalData ( hypre_CommPkg *comm_pkg , HYPRE_Complex **send_data , HYPRE_Complex **recv_data , HYPRE_Int action );
HYPRE_Int hypre_CommPkgDestroy ( hypre_CommPkg *comm_pkg );

/* struct_copy.c */
HYPRE_Int hypre_StructCopy ( hypre_StructVector *x , hypre_StructVector *y );
HYPRE_Int hypre_StructPartialCopy ( hypre_StructVector *x , hypre_StructVector *y , hypre_BoxArrayArray *array_boxes );

/* struct_data.c */
HYPRE_Int hypre_StructDataCopy ( HYPRE_Complex *fr_data , hypre_BoxArray *fr_data_space , HYPRE_Int *fr_ids , HYPRE_Complex *to_data , hypre_BoxArray *to_data_space , HYPRE_Int *to_ids , HYPRE_Int ndim , HYPRE_Int nval );
HYPRE_Int hypre_StructNumGhostFromStencil ( hypre_StructStencil *stencil , HYPRE_Int **num_ghost_ptr );

/* struct_grid.c */
HYPRE_Int hypre_StructGridCreate ( MPI_Comm comm , HYPRE_Int dim , hypre_StructGrid **grid_ptr );
HYPRE_Int hypre_StructGridRef ( hypre_StructGrid *grid , hypre_StructGrid **grid_ref );
HYPRE_Int hypre_StructGridDestroy ( hypre_StructGrid *grid );
HYPRE_Int hypre_StructGridSetPeriodic ( hypre_StructGrid *grid , hypre_Index periodic );
HYPRE_Int hypre_StructGridSetExtents ( hypre_StructGrid *grid , hypre_Index ilower , hypre_Index iupper );
HYPRE_Int hypre_StructGridSetBoxes ( hypre_StructGrid *grid , hypre_BoxArray *boxes );
HYPRE_Int hypre_StructGridSetBoundingBox ( hypre_StructGrid *grid , hypre_Box *new_bb );
HYPRE_Int hypre_StructGridSetIDs ( hypre_StructGrid *grid , HYPRE_Int *ids );
HYPRE_Int hypre_StructGridSetBoxManager ( hypre_StructGrid *grid , hypre_BoxManager *boxman );
HYPRE_Int hypre_StructGridSetMaxDistance ( hypre_StructGrid *grid , hypre_Index dist );
HYPRE_Int hypre_StructGridAssemble ( hypre_StructGrid *grid );
HYPRE_Int hypre_StructGridComputeBoxnums ( hypre_StructGrid *grid , HYPRE_Int nboxes , HYPRE_Int *boxnums , hypre_Index stride , HYPRE_Int *new_nboxes_ptr , HYPRE_Int **new_boxnums_ptr );
HYPRE_Int hypre_GatherAllBoxes ( MPI_Comm comm , hypre_BoxArray *boxes , HYPRE_Int dim , hypre_BoxArray **all_boxes_ptr , HYPRE_Int **all_procs_ptr , HYPRE_Int *first_local_ptr );
HYPRE_Int hypre_ComputeBoxnums ( hypre_BoxArray *boxes , HYPRE_Int *procs , HYPRE_Int **boxnums_ptr );
HYPRE_Int hypre_StructGridPrintVTK( const char *filename, hypre_StructGrid *grid );
HYPRE_Int hypre_StructGridPrint ( FILE *file , hypre_StructGrid *grid );
HYPRE_Int hypre_StructGridRead ( MPI_Comm comm , FILE *file , hypre_StructGrid **grid_ptr );
HYPRE_Int hypre_StructGridSetNumGhost ( hypre_StructGrid *grid , HYPRE_Int *num_ghost );

/* struct_innerprod.c */
HYPRE_Real hypre_StructInnerProdLocal ( hypre_StructVector *x , hypre_StructVector *y );
HYPRE_Real hypre_StructInnerProd ( hypre_StructVector *x , hypre_StructVector *y );

/* struct_io.c */
HYPRE_Int hypre_PrintBoxArrayData ( FILE *file , hypre_BoxArray *box_array , hypre_BoxArray *data_space , HYPRE_Int num_values , HYPRE_Int *value_ids , HYPRE_Int dim , HYPRE_Complex *data );
HYPRE_Int hypre_PrintCCVDBoxArrayData ( FILE *file , hypre_BoxArray *box_array , hypre_BoxArray *data_space , HYPRE_Int num_values , HYPRE_Int center_rank , HYPRE_Int stencil_size , HYPRE_Int *symm_offsets , HYPRE_Int dim , HYPRE_Complex *data );
HYPRE_Int hypre_PrintCCBoxArrayData ( FILE *file , hypre_BoxArray *box_array , hypre_BoxArray *data_space , HYPRE_Int num_values , HYPRE_Complex *data );
HYPRE_Int hypre_ReadBoxArrayData ( FILE *file , hypre_BoxArray *box_array , hypre_BoxArray *data_space , HYPRE_Int num_values , HYPRE_Int dim , HYPRE_Complex *data );
HYPRE_Int hypre_ReadBoxArrayData_CC ( FILE *file , hypre_BoxArray *box_array , hypre_BoxArray *data_space , HYPRE_Int stencil_size , HYPRE_Int real_stencil_size , HYPRE_Int constant_coefficient , HYPRE_Int dim , HYPRE_Complex *data );

/* struct_matmult.c */
HYPRE_Int hypre_StructMatmult ( HYPRE_Int nmatrices , hypre_StructMatrix **matrices , HYPRE_Int nterms , HYPRE_Int *terms , HYPRE_Int *transposes , hypre_StructMatrix **C_ptr );

/* struct_matrix.c */
HYPRE_Int hypre_StructMatrixGetDataMapStride ( hypre_StructMatrix *matrix , hypre_IndexRef *stride );
HYPRE_Int hypre_StructMatrixMapDataIndex ( hypre_StructMatrix *matrix , hypre_Index dindex );
HYPRE_Int hypre_StructMatrixMapDataBox ( hypre_StructMatrix *matrix , hypre_Box *dbox );
HYPRE_Int hypre_StructMatrixMapDataStride ( hypre_StructMatrix *matrix , hypre_Index dstride );
HYPRE_Int hypre_StructMatrixUnMapDataIndex ( hypre_StructMatrix *matrix , hypre_Index dindex );
HYPRE_Int hypre_StructMatrixUnMapDataBox ( hypre_StructMatrix *matrix , hypre_Box *dbox );
HYPRE_Int hypre_StructMatrixUnMapDataStride ( hypre_StructMatrix *matrix , hypre_Index dstride );
HYPRE_Int hypre_StructMatrixPlaceStencil ( hypre_StructMatrix *matrix , HYPRE_Int entry , hypre_Index dindex , hypre_Index index );
HYPRE_Int hypre_StructMatrixGetStencilStride ( hypre_StructMatrix *matrix , hypre_Index stride );
HYPRE_Int hypre_StructMatrixGetStencilSpace ( hypre_StructMatrix *matrix , HYPRE_Int entry , HYPRE_Int transpose , hypre_Index origin , hypre_Index stride );
HYPRE_Int hypre_StructMatrixMapCommInfo ( hypre_StructMatrix *matrix , hypre_IndexRef origin , hypre_Index stride , hypre_CommInfo *comm_info );
HYPRE_Int hypre_StructMatrixCreateCommPkg( hypre_StructMatrix *matrix , hypre_CommInfo *comm_info , hypre_CommPkg **comm_pkg_ptr , HYPRE_Complex ***comm_data_ptr);
HYPRE_Complex *hypre_StructMatrixExtractPointerByIndex ( hypre_StructMatrix *matrix , HYPRE_Int b , hypre_Index index );
hypre_StructMatrix *hypre_StructMatrixCreate ( MPI_Comm comm , hypre_StructGrid *grid , hypre_StructStencil *user_stencil );
hypre_StructMatrix *hypre_StructMatrixRef ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixDestroy ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixSetRangeBoxnums ( hypre_StructMatrix *matrix , HYPRE_Int range_nboxes , HYPRE_Int *range_boxnums , hypre_IndexRef range_stride );
HYPRE_Int hypre_StructMatrixSetRangeStride ( hypre_StructMatrix *matrix , hypre_IndexRef range_stride );
HYPRE_Int hypre_StructMatrixSetDomainBoxnums ( hypre_StructMatrix *matrix , HYPRE_Int domain_nboxes , HYPRE_Int *domain_boxnums , hypre_IndexRef domain_stride );
HYPRE_Int hypre_StructMatrixSetDomainStride ( hypre_StructMatrix *matrix , hypre_IndexRef domain_stride );
HYPRE_Int hypre_StructMatrixComputeDataSpace ( hypre_StructMatrix *matrix , HYPRE_Int *num_ghost , hypre_BoxArray **data_space_ptr );
HYPRE_Int hypre_StructMatrixResize ( hypre_StructMatrix *matrix , hypre_BoxArray *data_space );
HYPRE_Int hypre_StructMatrixRestore ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixForget ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixInitializeShell ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixInitializeData ( hypre_StructMatrix *matrix , HYPRE_Complex *data );
HYPRE_Int hypre_StructMatrixInitialize ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixSetValues ( hypre_StructMatrix *matrix , hypre_Index grid_index , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices , HYPRE_Complex *values , HYPRE_Int action , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructMatrixSetBoxValues ( hypre_StructMatrix *matrix , hypre_Box *set_box , hypre_Box *value_box , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices , HYPRE_Complex *values , HYPRE_Int action , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructMatrixSetConstantValues ( hypre_StructMatrix *matrix , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices , HYPRE_Complex *values , HYPRE_Int action );
HYPRE_Int hypre_StructMatrixClearValues ( hypre_StructMatrix *matrix , hypre_Index grid_index , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructMatrixClearBoxValues ( hypre_StructMatrix *matrix , hypre_Box *clear_box , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructMatrixAssemble ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixSetConstantEntries ( hypre_StructMatrix *matrix , HYPRE_Int nentries , HYPRE_Int *entries );
HYPRE_Int hypre_StructMatrixSetTranspose ( hypre_StructMatrix *matrix , HYPRE_Int transpose , HYPRE_Int *resize );
HYPRE_Int hypre_StructMatrixSetNumGhost ( hypre_StructMatrix *matrix , HYPRE_Int *num_ghost , HYPRE_Int *resize );
HYPRE_Int hypre_StructMatrixSetGhost ( hypre_StructMatrix *matrix , HYPRE_Int ghost , HYPRE_Int *resize );
HYPRE_Int hypre_StructMatrixClearGhostValues ( hypre_StructMatrix *matrix );
HYPRE_Int hypre_StructMatrixPrint ( const char *filename , hypre_StructMatrix *matrix , HYPRE_Int all );
HYPRE_Int hypre_StructMatrixMigrate ( hypre_StructMatrix *from_matrix , hypre_StructMatrix *to_matrix );
hypre_StructMatrix *hypre_StructMatrixRead ( MPI_Comm comm , const char *filename , HYPRE_Int *num_ghost );
HYPRE_Int hypre_StructMatrixClearBoundary( hypre_StructMatrix *matrix);

/* struct_matrix_mask.c */
hypre_StructMatrix *hypre_StructMatrixCreateMask ( hypre_StructMatrix *matrix , HYPRE_Int num_stencil_indices , HYPRE_Int *stencil_indices );

/* struct_matvec.c */
void *hypre_StructMatvecCreate ( void );
HYPRE_Int hypre_StructMatvecSetTranspose ( void *matvec_vdata , HYPRE_Int transpose );
HYPRE_Int hypre_StructMatvecSetSkipDiag ( void *matvec_vdata , HYPRE_Int skip_diag );
HYPRE_Int hypre_StructMatvecSetup ( void *matvec_vdata , hypre_StructMatrix *A , hypre_StructVector *x );
HYPRE_Int hypre_StructMatvecCompute ( void *matvec_vdata , HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector *y );
HYPRE_Int hypre_StructMatvecRectglCompute ( void *matvec_vdata , HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector *y );
HYPRE_Int hypre_StructMatvecSquareCompute ( void *matvec_vdata , HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector *y );
HYPRE_Int hypre_StructMatvecDiagScale ( HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector  *y );
HYPRE_Int hypre_StructMatvecDestroy ( void *matvec_vdata );
HYPRE_Int hypre_StructMatvec ( HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector *y );
HYPRE_Int hypre_StructMatvecT ( HYPRE_Complex alpha , hypre_StructMatrix *A , hypre_StructVector *x , HYPRE_Complex beta , hypre_StructVector *y );

/* struct_scale.c */
HYPRE_Int hypre_StructScale ( HYPRE_Complex alpha , hypre_StructVector *y );

/* struct_stencil.c */
hypre_StructStencil *hypre_StructStencilCreate ( HYPRE_Int dim , HYPRE_Int size , hypre_Index *shape );
hypre_StructStencil *hypre_StructStencilRef ( hypre_StructStencil *stencil );
HYPRE_Int hypre_StructStencilDestroy ( hypre_StructStencil *stencil );
HYPRE_Int hypre_StructStencilOffsetEntry ( hypre_StructStencil *stencil , hypre_Index stencil_offset );
HYPRE_Int hypre_StructStencilSymmetrize ( hypre_StructStencil *stencil , hypre_StructStencil **symm_stencil_ptr , HYPRE_Int **symm_offsets_ptr );

/* struct_vector.c */
HYPRE_Int hypre_StructVectorMapDataIndex ( hypre_StructVector *vector , hypre_Index dindex );
HYPRE_Int hypre_StructVectorMapDataBox ( hypre_StructVector *vector , hypre_Box *dbox );
HYPRE_Int hypre_StructVectorMapDataStride ( hypre_StructVector *vector , hypre_Index dstride );
HYPRE_Int hypre_StructVectorUnMapDataIndex ( hypre_StructVector *vector , hypre_Index dindex );
HYPRE_Int hypre_StructVectorUnMapDataBox ( hypre_StructVector *vector , hypre_Box *dbox );
HYPRE_Int hypre_StructVectorUnMapDataStride ( hypre_StructVector *vector , hypre_Index dstride );
HYPRE_Int hypre_StructVectorMapCommInfo ( hypre_StructVector *vector , hypre_CommInfo *comm_info );
hypre_StructVector *hypre_StructVectorCreate ( MPI_Comm comm , hypre_StructGrid *grid );
hypre_StructVector *hypre_StructVectorRef ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorDestroy ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorSetBoxnums ( hypre_StructVector *vector , HYPRE_Int nboxes , HYPRE_Int *boxnums , hypre_IndexRef stride );
HYPRE_Int hypre_StructVectorSetStride ( hypre_StructVector *vector , hypre_IndexRef stride );
HYPRE_Int hypre_StructVectorReindex ( hypre_StructVector *vector , hypre_StructGrid *grid , hypre_Index stride );
HYPRE_Int hypre_StructVectorComputeDataSpace ( hypre_StructVector *vector , HYPRE_Int *num_ghost , hypre_BoxArray **data_space_ptr );
HYPRE_Int hypre_StructVectorResize ( hypre_StructVector *vector , hypre_BoxArray     *data_space );
HYPRE_Int hypre_StructVectorRestore ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorForget ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorInitializeShell ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorInitializeData ( hypre_StructVector *vector , HYPRE_Complex *data );
HYPRE_Int hypre_StructVectorInitialize ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorSetValues ( hypre_StructVector *vector , hypre_Index grid_index , HYPRE_Complex *values , HYPRE_Int action , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructVectorSetBoxValues ( hypre_StructVector *vector , hypre_Box *set_box , hypre_Box *value_box , HYPRE_Complex *values , HYPRE_Int action , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructVectorClearValues ( hypre_StructVector *vector , hypre_Index grid_index , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructVectorClearBoxValues ( hypre_StructVector *vector , hypre_Box *clear_box , HYPRE_Int boxnum , HYPRE_Int outside );
HYPRE_Int hypre_StructVectorClearAllValues ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorSetNumGhost ( hypre_StructVector *vector , HYPRE_Int *num_ghost );
HYPRE_Int hypre_StructVectorAssemble ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorCopy ( hypre_StructVector *x , hypre_StructVector *y );
HYPRE_Int hypre_StructVectorSetConstantValues ( hypre_StructVector *vector , HYPRE_Complex value );
HYPRE_Int hypre_StructVectorSetRandomValues ( hypre_StructVector *vector, HYPRE_Int seed );
HYPRE_Int hypre_StructVectorSetFunctionValues ( hypre_StructVector *vector , HYPRE_Complex (*fcn )());
HYPRE_Int hypre_StructVectorClearGhostValues ( hypre_StructVector *vector );
HYPRE_Int hypre_StructVectorClearBoundGhostValues ( hypre_StructVector *vector , HYPRE_Int force );
HYPRE_Int hypre_StructVectorScaleValues ( hypre_StructVector *vector , HYPRE_Complex factor );
hypre_CommPkg *hypre_StructVectorGetMigrateCommPkg ( hypre_StructVector *from_vector , hypre_StructVector *to_vector );
HYPRE_Int hypre_StructVectorMigrate ( hypre_CommPkg *comm_pkg , hypre_StructVector *from_vector , hypre_StructVector *to_vector );
HYPRE_Int hypre_StructVectorPrint ( const char *filename , hypre_StructVector *vector , HYPRE_Int all );
hypre_StructVector *hypre_StructVectorRead ( MPI_Comm comm , const char *filename , HYPRE_Int *num_ghost );
HYPRE_Int hypre_StructVectorMaxValue ( hypre_StructVector *vector , HYPRE_Real *max_value , HYPRE_Int *max_index , hypre_Index max_xyz_index );
hypre_StructVector *hypre_StructVectorClone ( hypre_StructVector *vector );

#ifdef __cplusplus
}
#endif

#endif
