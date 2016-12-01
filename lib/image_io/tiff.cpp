/*
 * Copyright (c) 2008-2016 the MRtrix3 contributors
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/
 * 
 * MRtrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * For more details, see www.mrtrix.org
 * 
 */

#ifdef MRTRIX_TIFF_SUPPORT

#include "header.h"
#include "image_helpers.h"
#include "file/tiff.h"
#include "image_io/tiff.h"

namespace MR
{
  namespace ImageIO
  {

    void TIFF::load (const Header& header, size_t)
    {
      DEBUG ("allocating buffer for TIFF image \"" + header.name() + "\"...");
      addresses.resize (1);
      addresses[0].reset (new uint8_t [footprint (header)]);

      File::TIFF tif (header.name());

      uint16 config (0);
      tif.read_and_check (TIFFTAG_PLANARCONFIG, config);

      size_t scanline_size = tif.scanline_size();
      uint8_t* data = addresses[0].get();

      do {

        if (header.ndim() == 3 || config == PLANARCONFIG_CONTIG) {
          for (size_t row = 0; row < header.size(1); ++row) {
            tif.read_scanline (data, row);
            data += scanline_size;
          }
        }
        else if (config == PLANARCONFIG_SEPARATE) {
          for (size_t s = 0; s < header.size(3); s++) {
            for (size_t row = 0; row < header.size(1); ++row) {
              tif.read_scanline (data, row, s);
              data += scanline_size;
            }
          }
        }

      } while (tif.read_directory() != 0);

    }


    void TIFF::unload (const Header& header)
    {
      if (addresses.size()) {
        DEBUG ("deleting buffer for TIFF image \"" + header.name() + "\"...");
        addresses[0].release();
      }
    }

  }
}

#endif