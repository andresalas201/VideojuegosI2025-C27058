scene = {
    next_scenes = {
        win = "level_01_win",
        lose = "level_01_lose"
    },
    -- Tabla de imagenes y sprites
    sprites = {
        [0] =
        {
            assetId = "Bg_01",
            filePath = "assets/images/Background1.png"
        },
        {
            assetId = "player_ship",
            filePath = "assets/images/player_ship.png"
        },
        {
            assetId = "energy_shot",
            filePath = "assets/images/energy_shot.png"
        },
        {
            assetId = "icons",
            filePath = "assets/images/icons.png"
        },
        {
            assetId = "laser_bolt",
            filePath = "assets/images/LaserBolt.png"
        },
        {
            assetId = "cruiser",
            filePath = "assets/images/Cruiser.png"
        },
        {
            assetId = "enemy_alan",
            filePath = "assets/images/Improved_Alan.png"
        },
        {
            assetId = "missile",
            filePath = "assets/images/Missiles.png"
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
        filePath = "assets/music/z-battle.wav",
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
    -- Tabla de enemigos
    enemies = {
        [0] =
        { -- Alan
            group_left = 3,
            spawn_wait = 1,
            animation = {
                num_frames = 6,
                frame_rate = 6,
                is_loop = true,
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
        },
        { -- Alan
            group_left = 5,
            spawn_wait = 1,
            animation = {
                num_frames = 6,
                frame_rate = 6,
                is_loop = true,
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
                script = "assets/scripts/upgrade_damage.lua",
                width = 32,
                height = 32,
                rotation = 0,
                texture = "icons",
                src_x = 12*32,
                src_y = 10*32,
                sound = "upgrade",
                radius = 16
            }

        },
        -- Missiles
        {
            group_left = 1,
            spawn_wait = 10,
            animation = {
                num_frames = 4,
                frame_rate = 4,
                is_loop = true,
            },
            radius = 8,
            width = 16,
            height = 16,
            update_path = "assets/scripts/basic_enemy_follow.lua",
            health = 2,
            damage = 1,
            vel_x = -100,
            vel_y = 0,
            sound = {sound_name = "explosion"},
            texture = "missile",
            src_x = 0,
            src_y = 0,
            hit_x = 64,
            hit_y = 0,
            up_x = 0,
            down_x = 0,
            hit_down_x = 0,
            hit_up_x = 0,
            death_x =  128,
            death_y = 0,
            scale_x = 4.0,
            scale_y = 4.0,
            rotation = 0.0,
            drop = {
                increase = 5,
                script = "assets/scripts/upgrade_speed.lua",
                width = 32,
                height = 32,
                rotation = 0,
                texture = "icons",
                src_x = 2*32,
                src_y = 3*32,
                sound = "upgrade",
                radius = 16
            }
        },
        {
            group_left = 3,
            spawn_wait = 10,
            animation = {
                num_frames = 4,
                frame_rate = 4,
                is_loop = true,
            },
            radius = 8,
            width = 16,
            height = 16,
            update_path = "assets/scripts/basic_enemy_follow.lua",
            health = 2,
            damage = 1,
            vel_x = -100,
            vel_y = 0,
            sound = {sound_name = "explosion"},
            texture = "missile",
            src_x = 0,
            src_y = 0,
            hit_x = 64,
            hit_y = 0,
            up_x = 0,
            down_x = 0,
            hit_down_x = 0,
            hit_up_x = 0,
            death_x =  128,
            death_y = 0,
            scale_x = 4.0,
            scale_y = 4.0,
            rotation = 0.0,
            drop = {
                increase = 5,
                script = "assets/scripts/upgrade_speed.lua",
                width = 32,
                height = 32,
                rotation = 0,
                texture = "icons",
                src_x = 2*32,
                src_y = 3*32,
                sound = "upgrade",
                radius = 16
            }

        },
        -- Cruiser
        {
            group_left = 1,
            spawn_wait = 5,
            animation = {
                num_frames = 5,
                frame_rate = 5,
                is_loop = true,
            },
            attack = {
                damage = 5,
                radius = 8,
                width = 16,
                height = 16,
                texture = "energy_shot",
                src_x = 16,
                src_y = 0,
                vel = { x = 0, y = 0},
                sound = "laser_shot",
                hit_sound = "explosion",
                max_shots = 2,
                left = true,
                scale_x = 2,
                scale_y = 2,
                shot_quantity = 1,
                num_frames = 1,
                frame_speed_rate = 1,
                is_loop = true;
                attack_path = "assets/scripts/basic_enemy_follow_once.lua"
            },
            radius = 128,
            width = 512,
            height = 512,
            update_path = "assets/scripts/basic_enemy_shoot.lua",
            health = 3,
            damage = 1,
            vel_x = -100,
            vel_y = 0,
            sound = {sound_name = "explosion"},
            texture = "cruiser",
            src_x = 0,
            src_y = 0,
            hit_x = 2560,
            hit_y = 0,
            up_x = 0,
            down_x = 0,
            hit_down_x = 0,
            hit_up_x = 0,
            death_x =  5120,
            death_y = 0,
            scale_x = 0.25,
            scale_y = 0.25,
            rotation = 270.0,
            drop = {
                increase = 1,
                script = "assets/scripts/upgrade_amount.lua",
                width = 32,
                height = 32,
                rotation = 0,
                texture = "icons",
                src_x = 9*32,
                src_y = 12*32,
                sound = "upgrade",
                radius = 16
            }

        },
        -- Jefe
        {
            group_left = 1,
            spawn_wait = 1,
            animation = {
                num_frames = 6,
                frame_rate = 6,
                is_loop = true,
            },
            radius = 8,
            width = 16,
            height = 16,
            update_path = "assets/scripts/boss_enemy_follow.lua",
            health = 20,
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
            scale_x = 10.0,
            scale_y = 10.0,
            rotation = 0.0,
            boss = { x = 100, y = 100}

        }
    },
    -- Tabla de entidades
    entities = {
        [0] = {
            components = {
                sprite = {
                    assetId = "Bg_01",
                    width = 200,
                    height = 200,
                    src_rect = {x = 0, y = 0 },
                    hit_rect = {x = 32, y = 0 },
                },
                transform = {
                    position = {x = 0.0, y = 0.0},
                    scale = {x = 10.0, y = 10.0},
                    rotation = 0.0
                },
                rigidBody = {
                    velocity = {x = -1, y = 0}
                },
                script = {
                    path = "assets/scripts/background_move.lua"
                }
            }
        },
        -- Health bar
        {
            components = {
                text = {
                    text = "Health: 0",
                    fontId = "press_start_24",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 50.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                health_bar = {
                    is_player1 = true;
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
                    max_shots = 10,
                    left = false,
                    scale = {x = 1, y = 1},
                    shot_quantity = 1
                }
            }
        },
        -- Score controller
        {
            components = {
                text = {
                    text = "Score: 0",
                    fontId = "press_start_24",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                score = {
                    is_score = true,
                    path = "assets/scripts/score_script.lua",
                    boss_score = 500;
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
    }
}
