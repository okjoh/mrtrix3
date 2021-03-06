/* Copyright (c) 2008-2017 the MRtrix3 contributors.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * MRtrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * For more details, see http://www.mrtrix.org/.
 */


#ifndef __math_stats_permutation_h__
#define __math_stats_permutation_h__

#include <vector>

#include "math/stats/typedefs.h"

namespace MR
{
  namespace Math
  {
    namespace Stats
    {
      namespace Permutation
      {



        using value_type = Math::Stats::value_type;
        using vector_type = Math::Stats::vector_type;



        bool is_duplicate (const vector<size_t>&, const vector<size_t>&);
        bool is_duplicate (const vector<size_t>&, const vector<vector<size_t> >&);

        // Note that this function does not take into account grouping of subjects and therefore generated
        // permutations are not guaranteed to be unique wrt the computed test statistic.
        // Providing the number of subjects is large then the likelihood of generating duplicates is low.
        void generate (const size_t num_perms,
                       const size_t num_subjects,
                       vector<vector<size_t> >& permutations,
                       const bool include_default);

        void statistic2pvalue (const vector_type& perm_dist, const vector_type& stats, vector_type& pvalues);


        vector<vector<size_t> > load_permutations_file (const std::string& filename);




      }
    }
  }
}

#endif
