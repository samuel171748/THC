//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ADKernel.h"

/**
 * Adds contribution due to thermo-migration to the Cahn-Hilliard equation
 **/
class SEF2 : public ADKernel
{
public:
  static InputParameters validParams();

  SEF2(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  // temperature variable
  const ADVariableValue & _C1;
  const ADVariableValue & _C2;





//  const ADVariableGradient & _grad_C;

  // Mobility property name
  const Real & _z1;
  const Real & _z2;
  const Real & _Perm;
  const Real _F;
};
