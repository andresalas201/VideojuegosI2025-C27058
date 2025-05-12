scene = {
    -- Tabla de imagenes y sprites
    sprites = {
        [0] = 
        {
            assetId = "Bg_01",
            filePath = "assets/images/MenuBg.png"
        },
        {
            assetId = "player_ship",
            filePath = "assets/images/player_ship.png"
        },
        {
            assetId = "enemy_alan",
            filePath = "assets/images/enemy_alan.png"
        },
        {
            assetId = "energy_shot",
            filePath = "assets/images/energy_shot.png"
        }

    },
    -- Tabla de fuentes

    fonts = {
        [0] = {
            fontId = "press_start_24",
            filePath = "assets/fonts/press_start.ttf",
            fontSize = 24
        }
    },

    -- Tabla de acciones y teclas
    keys = {
        [0] =
        {name = "up", key=119},
        {name = "left", key=97},
        {name = "down", key=115},
        {name = "right", key=100},
        {name = "shoot", key=106}, -- J
    },

    -- Tabla de acciones y botones del ratón

    buttons = {
        [0] =
        {name = "mouse_left_button", button = 1},

    },
    music = {
        filePath = "assets/music/TestMusic.wav",
        length = 300,
    },
    -- Tabla de entidades
    entities = {
        [0] = {
            components = {
                sprite = {
                    assetId = "Bg_01",
                    width = 1280,
                    height = 720,
                    src_rect = {x = 0, y = 0 }
                },
                transform = {
                    position = {x = 0.0, y = 0.0},
                    scale = {x = 10.0, y = 10.0},
                    rotation = 0.0
                }
            }
        },
        -- Player
        {
            components = {
                circle_collider = {
                    radius = 8,
                    width = 16,
                    height = 16
                },
                rigidBody = {
                    velocity = {x = 0, y = 0}
                },
                script = {
                    path = "assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "player_ship",
                    width = 16,
                    height = 16,
                    src_rect = {x = 16, y = 0 }
                },
                transform = {
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 90.0
                },
                health = {
                    max_health = 10,
                    damage = 1
                },
                player = {
                    number = 1
                },
                attack = {
                    damage = 1,
                    radius = 8,
                    width = 16,
                    height = 16,
                    texture_id = "energy_shot",
                    src_x = 16,
                    src_y = 0,
                    vel_x = 100,
                    vel_y = 0,
                    sound_path = "assets/sounds/shot.wav",
                    hit_path = "assets/sounds/shot.wav",
                    max_shots = 5,
                    left = false,
                    scale = {x = 1, y = 1},
                    rotation = 0
                }
            }
        },
        {
            components = {
                circle_collider = {
                    radius = 8,
                    width = 16,
                    height = 16
                },
                rigidBody = {
                    velocity = {x = -1, y = 0}
                },
                sprite = {
                    assetId = "enemy_alan",
                    width = 16,
                    height = 16,
                    src_rect = {x = 16, y = 0 }
                },
                transform = {
                    position = {x = 800.0, y = 300.0},
                    scale = {x = 4.0, y = 4.0},
                    rotation = 180.0
                },
                health = {
                    max_health = 1,
                    damage = 1
                },
            }
        },
        {
            components = {
                text = {
                    text = "Score: 100",
                    fontId = "press_start_24",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 500.0, y = 50.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                clickable = {
                },
                
            }
        },
        {

        },
    }
}
