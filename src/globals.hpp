#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_
//========================================================================================
// Athena++ astrophysical MHD code
// Copyright(C) 2014 James M. Stone <jmstone@princeton.edu> and other code contributors
// Licensed under the 3-clause BSD License, see LICENSE file for details
//========================================================================================
//! \file globals.hpp
//! \brief namespace containing external global variables

namespace Globals {
extern int my_rank, nranks;
extern int next_task_id;
extern int next_scalar_index;
}

#endif // GLOBALS_HPP_
