/* ***************************************************************************
 *
 *  Copyright (C) 2013-2016 University of Dundee
 *  All rights reserved. 
 *
 *  This file is part of SAMoS (Soft Active Matter on Surfaces) program.
 *
 *  SAMoS is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  SAMoS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ****************************************************************************/

/*!
 * \file external_afpolar_aligner.cpp (based on external ajpolar_aligner.cpp)
 * \author Silke Henkes, silkehenkes@gmail.com
 * \author P Romanczuk, romanczuk.pawel@gmail.com
 * \date 12-Sep-2025
 * \brief Declaration of ExternalAJPolarAlign class
 */ 


#include "external_afpolar_aligner.hpp"

void ExternalAFPolarAlign::compute()
{
  int N = m_system->size();
  double tau = m_tau;
  
  
  for  (int i = 0; i < N; i++)
  {
    Particle& pi = m_system->get_particle(i);
    // The active jamming torque is:
    // 1/tau(\theta_v-theta_i); use variant 1/tau sin(\theta_v-theta_i)
    // or in vectorial: -1/tau (n_i \times v_i). ez
    // or calculate that vector and then give it to the projection
    double fx = pi.fx, fy = pi.fy, fz = pi.fz;
    if (m_normalise)
    {
      double f = sqrt(fx*fx + fy*fy + fz*fz);
      if (f > 0)
      {
        fx /= f;
        fy /= f;
        fz /= f;
      }
    }

    double tau_x = pi.ny*fz - pi.nz*fy;
    double tau_y = pi.nz*fx - pi.nx*fz;
    double tau_z = pi.nx*fy - pi.ny*fx;
    
    
    if (m_has_params)
      tau = m_type_params[pi.get_type()-1].tau;
    
    pi.tau_x += tau_x/tau;
    pi.tau_y += tau_y/tau;
    pi.tau_z += tau_z/tau;
    
  }
}
