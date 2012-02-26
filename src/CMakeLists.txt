set(KATE_QUICK_OPEN_PLUGIN_SOURCES
    quick_open_plugin_config_page.cpp
    quick_open_plugin_view.cpp
    quick_open_plugin.cpp
  )

kde4_add_ui_files(KATE_QUICK_OPEN_PLUGIN_SOURCES path_config.ui)

kde4_add_plugin(katequickopenplugin ${KATE_QUICK_OPEN_PLUGIN_SOURCES})

target_link_libraries(katequickopenplugin
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KFILE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    kateinterfaces
  )

install(TARGETS katequickopenplugin DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES ui.rc DESTINATION ${DATA_INSTALL_DIR}/katequickopenplugin)
install(FILES katequickopenplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})

# if (BUILD_TESTING)
#     add_subdirectory(test)
# endif()
