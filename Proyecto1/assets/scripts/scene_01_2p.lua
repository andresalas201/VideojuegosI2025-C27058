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
            assetId = "player_ship_2",
            filePath = "assets/images/player_ship_2.png"
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
        {name = "up2", key=1073741906}, -- Up arrow
        {name = "left2", key=1073741904}, -- Left arrow
        {name = "down2", key=1073741905}, -- Down arrow
        {name = "right2", key=1073741903}, -- Right arrow
        {name = "shoot2", key=1073741922}, -- Numpad 0
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
        {
            name = "explosion",
            file_path = "assets/sounds/explosion.wav"
        },
        {
            name = "scream",
            file_path = "assets/sounds/Death.wav"
        }

    },
    enemies = {
        [0] = {
            group_left = 3,
            spawn_wait = 1,
            animation = {
                num_frames = 6,
                frame_rate = 6,
                is_loop = true,
            },
            attack = {
                damage = 2,
                radius = 8,
                width = 16,
                height = 16,
                texture = "energy_shot",
                src_x = 16,
                src_y = 0,
                vel = { x = 100, y = 0},
                sound = "laser_shot",
                hit_sound = "explosion",
                max_shots = 5,
                left = true,
                scale_x = 1,
                scale_y = 1,
                shot_quantity = 1,
                num_frames = 1,
                frame_speed_rate = 1,
                is_loop = true;
                attack_path = "assets/scripts/basic_bullet.lua"
            },
            radius = 8,
            width = 16,
            height = 16,
            update_path = "assets/scripts/basic_enemy.lua",
            health = 1,
            damage = 1,
            vel_x = -100,
            vel_y = 0,
            sound = {sound_name = "scream"},
            texture = "enemy_alan",
            src_x = 0,
            src_y = 0,
            hit_x = 96,
            hit_y = 0,
            up_x = 0,
            down_x = 0,
            hit_down_x = 96,
            hit_up_x = 96,
            death_x =  192,
            death_y = 0,
            scale_x = 4.0,
            scale_y = 4.0,
            rotation = 0.0,
            drop = {
                increase = 1,
                script = "assets/scripts/upgrade_amount.lua",
                width = 32,
                height = 32,
                rotation = 0,
                texture = "icons",
                src_x = 2*32,
                src_y = 8*32,
                sound = "upgrade",
                radius = 16
            }

        }
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
                    hit_path = "explosion",
                    max_shots = 5,
                    left = false,
                    scale = {x = 1, y = 1},
                    shot_quantity = 1
                }
            }
        },
        -- Player 2
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
                    path = "assets/scripts/player2.lua"
                },
                sprite = {
                    assetId = "player_ship_2",
                    width = 16,
                    height = 16,
                    src_rect = {x = 16, y = 0 },
                    hit_rect = {x = 64, y = 0 },
                    up_down = {up = 0, down = 32, hit_up = 46, hit_down = 80},
                    death = {x = 96, y = 0}
                },
                transform = {
                    position = {x = 400.0, y = 400.0},
                    scale = {x = 4.0, y = 4.0},
                    rotation = 90.0
                },
                health = {
                    max_health = 1,
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
                    hit_path = "explosion",
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
