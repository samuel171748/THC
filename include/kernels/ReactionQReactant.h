/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#pragma once

#include "Kernel.h"

// Forward Declaration
class ReactionQReactant;

template <>
InputParameters validParams<ReactionQReactant>();

class ReactionQReactant : public Kernel
{
public:
  ReactionQReactant(const InputParameters & parameters);

protected:
  Real computeQpResidual() override;
  Real computeQpJacobian() override;
  Real computeQpOffDiagJacobian(unsigned int jvar) override;


  // The reaction coefficient
  const MaterialProperty<Real> & _Reaction_rate;
  const Real & _Num;
  const MaterialProperty<Real> & _Ea;
  const VariableValue & _T;
  const VariableValue & _v;
  unsigned _T_id;
};
