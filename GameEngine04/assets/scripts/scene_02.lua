scene = {
    -- Tabla de imagenes y sprites
    sprites = {
        [0] = {
            assetId = "frog_idle",
            filePath = "assets/images/frog_idle.png"
        },
        {
            assetId = "frog_jump",
            filePath = "assets/images/frog_jump.png"
        },
        {
            assetId = "frog_fall",
            filePath = "assets/images/frog_fall.png"
        },
        {
            assetId = "frog_run",
            filePath = "assets/images/frog_run.png"
        },
        {
            assetId = "background",
            filePath = "assets/images/background_space_oil6.png"
        },
        {
            assetId = "terrain",
            filePath = "assets/images/terrain.png"
        },
    },

    maps = {
        map_path = "assets/maps/level_01.tmx",
        tile_path = "assets/maps/terrain.tsx",
        tile_name = "terrain"
    },

    -- Tabla con info de animaciones
    animations = {
        [0] = 
        {animation_id = "player_frog_idle", texture_id = "frog_idle", w = 32, h = 32, num_frames = 11, speed_rate = 15, is_loop = true},
        {animation_id = "player_frog_jump", texture_id = "frog_jump", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
        {animation_id = "player_frog_fall", texture_id = "frog_fall", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
        {animation_id = "player_frog_run", texture_id = "frog_run", w = 32, h = 32, num_frames = 12, speed_rate = 15, is_loop = true},
    },

    fonts = {
        [0] = {
            fontId = "press_start_24",
            filePath = "assets/fonts/press_start.ttf",
            fontSize = 24
        },
        {
            fontId = "press_start_32",
            filePath = "assets/fonts/press_start.ttf",
            fontSize = 32
        }
    },

    -- Tabla de acciones y teclas
    keys = {
        [0] =
        {name = "up", key=119},
        {name = "left", key=97},
        {name = "down", key=115},
        {name = "right", key=100},
        {name = "jump", key=32},
    },

    -- Tabla de acciones y botones del ratón

    buttons = {
        [0] =
        {name = "mouse_left_button", button = 1},

    },

    -- Tabla de entidades
    entities = {
        [0] =
        -- Player
        {
            components = {
                animation = {
                    num_frames = 11,
                    speed_rate = 15,
                    is_loop = true
                },
                camera_follow = {},
                box_collider = {
                    width = 32,
                    height = 32,
                    offset = {x = 0, y = 0}
                },
                rigidBody = {
                    is_dynamic = true,
                    mass = 10,
                    is_solid = true
                },
                script = {
                    path = "assets/scripts/player_frog.lua"
                },
                sprite = {
                    assetId = "frog_idle",
                    width = 32,
                    height = 32,
                    src_rect = {x = 0, y = 0 }
                },
                tag = {
                    tag = "player"
                },
                transform = {
                    position = {x = 200.0, y = 100.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                }
            }
        },
    }
}
