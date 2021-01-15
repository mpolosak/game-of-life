project(
	'game-of-life',
    'c',
	'cpp',
	license: 'GPLv3',
	meson_version: '>=0.45.0',
)
sfml_graphics = dependency('sfml-graphics')
sfml_system = dependency('sfml-system')
sfml_window = dependency('sfml-window')
boost = dependency('boost', modules :['program_options'])
libpng = dependency('libpng')
pngpp = declare_dependency(include_directories: '/usr/include/png++')
subdir('src')