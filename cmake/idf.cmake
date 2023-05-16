# CMakeLists.txt of MOONCAKE component

# Source files directories
set(MOONCAKE_SRC_DIRS
    ${MOONCAKE_ROOT_DIR}/src/app/
    ${MOONCAKE_ROOT_DIR}/src/framework/
    ${MOONCAKE_ROOT_DIR}/src/simplekv/
)

# Head files directories
set(MOONCAKE_INC_DIRS
    ${MOONCAKE_ROOT_DIR}/src/
    ${MOONCAKE_ROOT_DIR}/src/app/
    ${MOONCAKE_ROOT_DIR}/src/framework/
    ${MOONCAKE_ROOT_DIR}/src/simplekv/
)

# Source files directories
set(MOONCAKE_BUILTIN_APPS_SRC_DIRS
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/boot_anim/
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/launcher/
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/launcher/icon
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/launcher/icon/anim/walking/walking/
)

# Head files directories
set(MOONCAKE_BUILTIN_APPS_INC_DIRS
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/boot_anim/
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/launcher/
    ${MOONCAKE_ROOT_DIR}/src/builtin_apps/launcher/icon/anim/walking/
)

# Public component requirement
set(MOONCAKE_REQUIRES
    lvgl
)

# Private component requirement
set(MOONCAKE_PRIV_REQUIRES
)

# Register component
idf_component_register(SRC_DIRS ${MOONCAKE_SRC_DIRS} ${MOONCAKE_BUILTIN_APPS_SRC_DIRS}
                  INCLUDE_DIRS ${MOONCAKE_INC_DIRS} ${MOONCAKE_BUILTIN_APPS_INC_DIRS}
                  REQUIRES ${MOONCAKE_REQUIRES}
                  PRIV_REQUIRES ${MOONCAKE_PRIV_REQUIRES}
)
