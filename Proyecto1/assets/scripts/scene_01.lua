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
            filePath = "assets/images/Improved_Alan.png"
        },
        {
            assetId = "energy_shot",
            filePath = "assets/images/energy_shot.png"
        },
        {
            assetId = "icons",
            filePath = "assets/images/icons.png"
        },

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
    sound = {
        [0] = {
            name = "laser_shot",
            file_path = "assets/sounds/shot.wav"
        },
        {
            name = "upgrade",
            file_path = "assets/sounds/upgrade.wav"
        },

    },
    -- Tabla de entidades
    entities = {
        [0] = {
            components = {
                sprite = {
                    assetId = "Bg_01",
                    width = 1280,
                    height = 720,
                    src_rect = {x = 0, y = 0 },
                    hit_rect = {x = 32, y = 0 },
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
                    src_rect = {x = 16, y = 0 },
                    hit_rect = {x = 64, y = 0 },
                    up_down = {up = 0, down = 32, hit_up = 46, hit_down = 80},
                    death = {x = 96, y = 0}
                },
                transform = {
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 4.0, y = 4.0},
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
                    sound_path = "laser_shot",
                    hit_path = "laser_shot",
                    max_shots = 5,
                    left = false,
                    scale = {x = 1, y = 1},
                    shot_quantity = 1
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
                    src_rect = {x = 0, y = 0 },
                    hit_rect = {x = 96, y = 0 },
                    death = {x =  192, y = 0}
                },
                animation = {
                    frames = 6,
                    frame_rate = 6,
                    looping = true,
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
                    src_rect = {x = 0, y = 0 },
                    hit_rect = {x = 96, y = 0 },
                    death = {x =  192, y = 0}
                },
                animation = {
                    frames = 6,
                    frame_rate = 6,
                    looping = true,
                },
                transform = {
                    position = {x = 800.0, y = 400.0},
                    scale = {x = 4.0, y = 4.0},
                    rotation = 0.0
                },
                health = {
                    max_health = 2,
                    damage = 1
                },
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
                    src_rect = {x = 0, y = 0 },
                    hit_rect = {x = 96, y = 0 },
                    death = {x =  192, y = 0}
                },
                animation = {
                    frames = 6,
                    frame_rate = 6,
                    looping = true,
                },
                transform = {
                    position = {x = 800.0, y = 500.0},
                    scale = {x = 4.0, y = 4.0},
                    rotation = 0.0
                },
                health = {
                    max_health = 2,
                    damage = 1
                },
            }
        },
        {
            components = {
                circle_collider = {
                    radius = 16,
                    width = 32,
                    height = 32
                },
                rigidBody = {
                    velocity = {x = -10, y = 0}
                },
                sprite = {
                    assetId = "icons",
                    width = 32,
                    height = 32,
                    src_rect = {x = 2*32, y = 8*32 },
                    hit_rect = {x = 2*32, y = 8*32 }
                },
                transform = {
                    position = {x = 800.0, y = 250.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                health = {
                    max_health = 1,
                    damage = 0
                },
                upgrade = {
                    increase = 1,
                    path = "assets/scripts/upgrade_amount.lua"
                },
                sound = {
                    sound_path = "upgrade"
                }
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
