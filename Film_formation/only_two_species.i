[Mesh]
  file = '2D_Cu_Sol_2021_01_20.msh'
[]

[Variables]
  # Name of chemical species
  [./Cu]
   block = 'Copper_domain Solution_domain'
   order = FIRST
  [../]
  [./Cu+]
   block = 'Copper_domain Solution_domain'
   order = FIRST
  [../]
  [./HS-]
   block = 'Copper_domain Solution_domain'
   order =FIRST
  [../]
  [./phi]
    block = 'Copper_domain Solution_domain'
    order = FIRST
    initial_condition = 0
  [../]
[]

[ICs]
  [./Copper_block_Cu]
    type = ConstantIC
    block = 'Copper_domain'
    variable = Cu
    value = 1 #[g/m3]
  [../]
  [./Copper_block_Cu+]
    type = ConstantIC
    block = 'Copper_domain'
    variable = Cu+
    value = 1 #[g/m3]
  [../]
  [./Copper_block_HS-]
    type = ConstantIC
    block = 'Copper_domain'
    variable = HS-
    value = 3
  [../]

  [./Solution_block_Cu]
    type = ConstantIC
    block = 'Solution_domain'
    variable = Cu
    value = 1
  [../]
  [./Solution_block_Cu+]
    type = ConstantIC
    block = 'Solution_domain'
    variable = Cu+
    value = 1
  [../]
 [./Solution_block_HS-]
    type = ConstantIC
    block = 'Solution_domain'
    variable = HS-
    value = 3
  [../]

[]


[Kernels]
# dCi/dt
  [./dCu_dt]
    block = 'Copper_domain Solution_domain'
    type = TimeDerivative
    variable = Cu
  [../]
  [./dCu+_dt]
    block = 'Copper_domain Solution_domain'
    type = TimeDerivative
    variable = Cu+
  [../]
  [./dHS-_dt]
    block = 'Copper_domain Solution_domain'
    type = TimeDerivative
    variable = HS-
  [../]

  [./DgradCu]
    block = 'Copper_domain Solution_domain'
    type = CoefDiffusion
    coef = 0 
    variable = Cu
  [../]
  [./DgradCu+]
    block = 'Copper_domain Solution_domain'
    type = CoefDiffusion
    coef = 1e-9
    variable = Cu+
  [../]
 
  [./DgradHS-_C]
    block = 'Copper_domain Solution_domain'
    type = CoefDiffusion
    coef = 5e-9
    variable = HS-
  [../]

  [./Cal_Potential_dist]
    block = 'Copper_domain Solution_domain'
    type = SEP2
    variable = phi
    CS1 = Cu+
    CS2 = HS-
    Charge1 = 1
    Charge2 = -1
  [../]


  [./Migration_HS-]
    block = 'Copper_domain Solution_domain'
    type = NernstPlanck
    T = 298.15
    variable = HS-
    Potential = phi
    Charge_coef = -1
    Diffusion_coef = 5E-9    
  [../]
  [./Migration_Cu+]
    block = 'Copper_domain Solution_domain'
    type = NernstPlanck
    T = 298.15
    variable = Cu+
    Potential = phi
    Charge_coef = -1
    Diffusion_coef = 1E-9    
  [../]
[]

[ChemicalReactions]
 [./Network]
   block = 'Copper_domain Solution_domain'
   species = 'Cu Cu+ HS-'
   track_rates = False
   equation_constants = 'Ea R T_Re'
   equation_values = '0 8.314 298.15'
#   equation_variables = 'T'

   reactions = 'Cu + HS- -> Cu+ : {1E10}'
 []
[]


[Executioner]
  type = Transient
  start_time = 0 #[s]
  end_time = 1000 #
  solve_type = 'PJFNK'
#  l_abs_tol = 1e-3 #1e-11 for HS- + H2O2
#  l_tol = 1e-5 #default = 1e-5
#  nl_abs_tol = 1e-2 #1e-11 for HS- + H2O2
  nl_rel_tol = 1e-1  #default = 1e-7
  l_max_its = 10
  nl_max_its = 10
#  dtmax = 10
#  dt = 0.5
  automatic_scaling = true
  compute_scaling_once = false
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.9
    dt = 1e-7
    growth_factor = 1.1
  [../]

#  [./Adaptivity]
#    refine_fraction = 0.3
#    max_h_level = 7
#    cycles_per_step = 2
#  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]



[Outputs]
  exodus = true
[]
