//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SEF2.h"

registerMooseObject("corrosionApp", SEF2);

InputParameters
SEF2::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("This kernel solve nernst-planck terms and should be combined with poisson term (diffusion)");
  params.addCoupledVar("CS1", 0,"Add name of chemical species");
  params.addCoupledVar("CS2", 0,"Add name of chemical species");
  params.addParam<Real>("Charge1", "Charge valence of chemical species");
  params.addParam<Real>("Charge2", "Charge valence of chemical species");
  params.addParam<Real>("Permittivity",1.0,"Permittivity by fixed space charge, unit: F/m, 1F = 1C/V F is not a faraday constant, F is called farad");
  return params;
}

SEF2::SEF2(const InputParameters & parameters)
  : ADKernel(parameters),
    _C1(adCoupledValue("CS1")),
    _C2(adCoupledValue("CS2")),
    _z1(getParam<Real>("Charge1")),
    _z2(getParam<Real>("Charge2")),
    _Perm(getParam<Real>("Permittivity")),
    _F(96485)
{
}

ADReal
SEF2::computeQpResidual()
{
  return (_z1  *  _C1[_qp] + _z2 * _C2[_qp]) * _F * _test[_i][_qp] -  _Perm * _grad_test[_i][_qp] * _grad_u[_qp];
}
