#include "Game.h"

Game::Game() {
    std::cout << "Se crea un game" << std::endl;
}

Game::~Game() {
    std::cout << "Se destruye un game" << std::endl;
}

void Game::initWindow(std::string reader[10]) {

    this->windowWidth = std::stoi(reader[1]);
    this->windowHeight = std::stoi(reader[2]);
    int red = std::stoi(reader[3]);
    int green = std::stoi(reader[4]);
    int blue = std::stoi(reader[5]);

    this->window = SDL_CreateWindow(
        "Tarea 1 - C27058", // Titulo
        SDL_WINDOWPOS_CENTERED, //Pos en X
        SDL_WINDOWPOS_CENTERED, // Pos en Y
        this->windowWidth,
        this->windowHeight,
        SDL_WINDOW_SHOWN
    );

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1, //driver index
        0 // flags
    );

    SDL_SetRenderDrawColor(this->renderer, red, green, blue, 255);
}

void Game::initFont(std::string reader[10]) {

    this->fontColor.r = std::stoi(reader[2]);
    this->fontColor.g = std::stoi(reader[3]);
    this->fontColor.b = std::stoi(reader[4]);
    this->fontSize = std::stoi(reader[5]);
    this->font = TTF_OpenFont(reader[1].c_str(), this->fontSize);

    if (!this->font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Game::initEntity(Entity* entity, std::string reader[10]) {
    
    entity->label = reader[1];
    entity->imgPath = reader[2];
    entity->imgWidth = std::stoi(reader[3]);
    entity->imgHeight = std::stoi(reader[4]);
    entity->pX  = std::stod(reader[5]);
    entity->pY = std::stod(reader[6]);
    entity->vX  = std::stod(reader[7]);
    entity->vY = std::stod(reader[8]);
    entity->angle  = std::stod(reader[9]);
    
    // Inicializar imagen
    SDL_Surface* imgSurface = IMG_Load(entity->imgPath.c_str());
    entity->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
    SDL_FreeSurface(imgSurface);
    entity->srcRect.x = 0;
    entity->srcRect.y = 0;
    entity->srcRect.w = entity->imgWidth;
    entity->srcRect.h = entity->imgHeight;

    if(entity->vX >= 0) entity->imgFlip = SDL_FLIP_NONE;
    else entity->imgFlip = SDL_FLIP_HORIZONTAL;
}

void Game::initText(Entity* entity) {
    
    // Inicializar Texto
    SDL_Surface* txtSurface = TTF_RenderText_Solid(
        this->font, 
        entity->label.c_str(), 
        this->fontColor
    );
    if (!txtSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return; // Or handle error appropriately
    }
    entity->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
    entity->txtWidth = txtSurface->w;
    entity->txtHeight = txtSurface->h;
    entity->txtPos.x = entity->pX  - (entity->txtWidth / 2) + (entity->imgWidth / 2);
    entity->txtPos.y = entity->pY;

    SDL_FreeSurface(txtSurface);
}

void Game::readConfig() {

    std::ifstream configArchive("assets/config/config.txt");
    std::string reader[10];
    
    configArchive >> reader[0] >> reader[1] >> reader[2] >> reader[3] >> reader[4] >> reader[5];
    initWindow(reader);
    

    configArchive >> reader[0] >> reader[1] >> reader[2] >> reader[3] >> reader[4] >> reader[5];
    initFont(reader);

    Entity* newEntity = nullptr;
    while(configArchive >> reader[0]) {
        newEntity = new Entity();
        configArchive >> reader[1] >> reader[2] >> reader[3] >> reader[4] >> reader[5]
                    >> reader[6] >> reader[7] >> reader[8] >> reader[9];
        initEntity(newEntity, reader);
        initText(newEntity);
        this->entities.push_back(newEntity);
    }
}

void Game::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error al inicializar SDL" << std::endl;
        return;
    }

    if(TTF_Init() < 0) {
        std::cerr << "Error al inicializar TTF" << std::endl;
        return;
    }

    this->isRunning = true;

    readConfig();    

}

void Game::run() {
    while(this->isRunning) {
        processInput();
        if(!this->isPaused) {
            update();
            render();
        }
    }

}

void Game::destroy() {
    for (int i = 0; i < int(this->entities.size()); i++) {
        SDL_DestroyTexture(this->entities[i]->imgTexture);
        SDL_DestroyTexture(this->entities[i]->txtTexture);
    }
    
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    TTF_CloseFont(this->font);
    
    Entity* currentEntity;
    while(this->entities.size() > 0) {
        currentEntity = this->entities.back();
        this->entities.pop_back();
        delete currentEntity;
    }

    SDL_Quit();
    TTF_Quit();
}

void Game::update() {
    // Calcular la espera, get ticks retorna la cantidad de ms desde que SDL inició
    int timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - this->mPrvsFrame);

    if(timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME) {
        SDL_Delay(timeToWait);
    }
    
    // Divide entre 1000 para pasarlo de ms a s
    double deltaTime = (SDL_GetTicks() - this->mPrvsFrame) / 1000.0;

    this->mPrvsFrame = SDL_GetTicks();

    moveEntity(deltaTime);

}

void Game::moveEntity(double deltaTime) {
    for (int i = 0; i < int(this->entities.size()); i++) {
        this->entities[i]->pX += this->entities[i]->vX * deltaTime;
        this->entities[i]->pY += this->entities[i]->vY * deltaTime;
        
        if(this->entities[i]->pX >= (this->windowWidth - this->entities[i]->imgWidth) || this->entities[i]->pX <= 0) {
            this->entities[i]->vX *= -1;
            if(this->entities[i]->imgFlip == SDL_FLIP_NONE) this->entities[i]->imgFlip = SDL_FLIP_HORIZONTAL;
            else this->entities[i]->imgFlip = SDL_FLIP_NONE;
        }

        if(this->entities[i]->pY >= (this->windowHeight - this->entities[i]->imgHeight) || this->entities[i]->pY <= 0)
        this->entities[i]->vY *= -1;

        this->entities[i]->txtPos.x = this->entities[i]->pX  - (this->entities[i]->txtWidth / 2) + (this->entities[i]->imgWidth / 2);
        this->entities[i]->txtPos.y = this->entities[i]->pY ;
    }

}

void Game::processInput() {
    SDL_Event sdlEvent;
    // PollEvent saca un evento y lo guarda en un SDL_Event
    while(SDL_PollEvent(&sdlEvent)) {
        switch(sdlEvent.type) {
            case SDL_QUIT:
                this->isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    this->isRunning = false;
                } else if(sdlEvent.key.keysym.sym == SDLK_p) {
                    this->isPaused = !this->isPaused;
                    this->mPrvsFrame = SDL_GetTicks();
                }
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    SDL_Rect imgDstRect, txtDstRect;
    for (int i = 0; i < int(this->entities.size()); i++) {
        imgDstRect = {
            int(this->entities[i]->pX),
            int(this->entities[i]->pY),
            this->entities[i]->imgWidth,
            this->entities[i]->imgHeight
        };

        txtDstRect = {
            int(this->entities[i]->txtPos.x),
            int(this->entities[i]->txtPos.y),
            this->entities[i]->txtWidth,
            this->entities[i]->txtHeight
        };
        
        // Dibujar imagen
        
        SDL_RenderCopyEx(
            this->renderer,
            this->entities[i]->imgTexture,
            &this->entities[i]->srcRect,
            &imgDstRect,
            this->entities[i]->angle,
            NULL,
            this->entities[i]->imgFlip
        );

        // Dibujar Texto

        SDL_RenderCopyEx(
            this->renderer,
            this->entities[i]->txtTexture,
            NULL, // El null dibuja toda la textura
            &txtDstRect,
            this->entities[i]->txtAngle,
            NULL,
            SDL_FLIP_NONE
        );
    }

    SDL_RenderPresent(this->renderer);
}

