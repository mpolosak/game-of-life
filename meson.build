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
pngpp_dir=get_option('pngpp_dir')
pngpp = declare_dependency(include_directories: include_directories(pngpp_dir))
subdir('src')
install_data('game-of-life.desktop', install_dir: 'share/applications')
install_subdir('icons', install_dir: 'share/icons/hicolor', strip_directory: true)