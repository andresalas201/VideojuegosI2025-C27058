scene = {
    -- Tabla de imagenes y sprites
    sprites = {
        [0] =
        {
            assetId = "Bg_01",
            filePath = "assets/images/LoseBackground.png"
        },
    },
    -- Tabla de fuentes

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
    },

    -- Tabla de acciones y botones del ratón

    buttons = {
        [0] =
        {name = "mouse_left_button", button = 1},

    },
    music = {
        filePath = "assets/music/Defeat.wav",
        length = 2000,
    },

    -- Tabla de entidades
    entities = {
        [0] =
        {
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
        {
            components = {
                text = {
                    text = "You have lost, General Glup will conquer Andronika",
                    fontId = "press_start_32",
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
                clickable = {
                }
            },
        },
        {
            components = {
                text = {
                    text = "Retry - 1 Player",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 100.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                script = {
                    path = "assets/scripts/menu_button_03.lua"
                },
                player = {
                    number = 1
                },
                clickable = {
                }
            }
        },
        {
            components = {
                text = {
                    text = "Retry - 2 Players",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 150.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                script = {
                    path = "assets/scripts/menu_button_04.lua"
                },
                clickable = {
                }
            }
        },
        {
            components = {
                text = {
                    text = "Return to main menu",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 200.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0
                },
                script = {
                    path = "assets/scripts/menu_button_07.lua"
                },
                clickable = {
                }
            }
        }
    }
}
