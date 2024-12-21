project('Raycasting-game', 'cpp',
  version: '1.0',
  default_options: ['cpp_std=c++17', 'warning_level=2', 'debug=true']
)
build_dir = '../build'
sources = [
  'main.cpp',
  'map.cpp',
  'renderer.cpp',
  'player.cpp',
  'raycast.cpp'
]
sfml_dep = dependency('sfml-graphics', required: true)
sfml_window_dep = dependency('sfml-window', required: true)
sfml_system_dep = dependency('sfml-system', required: true)
include_dirs = include_directories([
  '../libs/SFML/include',
  '../libs/include',
  '../libs/yaml-cpp/include'
])
yaml_cpp = dependency('yaml-cpp', required: false)
executable('Raycasting-game',
  sources,
  include_directories: include_dirs,
  dependencies: [sfml_dep, sfml_window_dep, sfml_system_dep, yaml_cpp],
  install: true
)
