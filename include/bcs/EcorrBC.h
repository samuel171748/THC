//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "DirichletBCBase.h"

class EcorrBC;

template <>
InputParameters validParams<EcorrBC>();

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value in the node
 */
class EcorrBC : public DirichletBCBase
{
public:
  static InputParameters validParams();

  EcorrBC(const InputParameters & parameters);

protected:
  virtual Real computeQpValue() override;

  /// The value for this BC
  const VariableValue & _value;
};
