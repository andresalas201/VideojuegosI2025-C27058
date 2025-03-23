#include "Game.h"

Game::Game() {
    std::cout << "Se crea un game" << std::endl;
}

Game::~Game() {
    std::cout << "Se destruye un game" << std::endl;
}

void Game::initWindow(int red, int green, int blue) {

    this->window = SDL_CreateWindow(
        "Intro a SDL", // Titulo
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

void Game::initFont(std::string path) {
    //Cargar texto
    
    this->font = TTF_OpenFont(path.c_str(), this->fontSize);


}

void Game::initEntity() {
    // Inicializar imagen
    SDL_Surface* imgSurface = IMG_Load(this->entity->imgPath.c_str());
    this->entity->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
    SDL_FreeSurface(imgSurface);
    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = this->entity->imgWidth;
    this->srcRect.h = this->entity->imgHeight;
}

void Game::initText() {
        // Inicializar Texto

    SDL_Surface* txtSurface = TTF_RenderText_Solid(
        this->font, 
        this->entity->label.c_str(), 
        this->fontColor
    );
    this->entity->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
    this->entity->txtWidth = txtSurface->w;
    this->entity->txtHeight = txtSurface->h;
    this->entity->txtPos.x = this->entity->pX  - (this->entity->txtWidth / 2) + (this->entity->imgWidth / 2);
    this->entity->txtPos.y = this->entity->pY - 20;

    SDL_FreeSurface(txtSurface);
}

void Game::readConfig() {

    std::ifstream configArchive("assets/config/config.txt");
    std::string reader;
    configArchive >> reader;
    this->windowWidth = std::stoi(reader);
    configArchive >> reader;
    this->windowHeight = std::stoi(reader);
    configArchive >> reader;
    int red = std::stoi(reader);
    configArchive >> reader;
    int green = std::stoi(reader);
    configArchive >> reader;
    int blue = std::stoi(reader);
    initWindow(red, green, blue);

    std::string path;
    configArchive >> path;
    configArchive >> reader;
    this->fontColor.r = std::stoi(reader);
    configArchive >> reader;
    this->fontColor.g = std::stoi(reader);
    configArchive >> reader;
    this->fontColor.b = std::stoi(reader);
    configArchive >> reader;
    this->fontSize = std::stoi(reader);
    initFont(path);

    
    this->entity = new Entity();
    configArchive >> this->entity->label;
    configArchive >> this->entity->imgPath;
    configArchive >> reader;
    this->entity->imgWidth = std::stoi(reader);
    configArchive >> reader;
    this->entity->imgHeight = std::stoi(reader);
    configArchive >> reader;
    this->entity->pX  = std::stod(reader);
    configArchive >> reader;
    this->entity->pY = std::stod(reader);
    configArchive >> reader;
    this->entity->vX  = std::stod(reader);
    configArchive >> reader;
    this->entity->vY = std::stod(reader);
    configArchive >> reader;
    this->entity->angle  = std::stod(reader);
    initEntity();
    initText();
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
    SDL_DestroyTexture(this->entity->imgTexture);
    SDL_DestroyTexture(this->entity->txtTexture);
    
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    TTF_CloseFont(this->font);
    
    delete this->entity;

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
    this->entity->pX += this->entity->vX * deltaTime;
    this->entity->pY += this->entity->vY * deltaTime;
    
    if(this->entity->pX >= (this->windowWidth-this->entity->imgWidth) || this->entity->pX <= 0) {
        this->entity->vX *= -1;
        if(this->entity->imgFlip == SDL_FLIP_NONE) this->entity->imgFlip = SDL_FLIP_HORIZONTAL;
        else this->entity->imgFlip = SDL_FLIP_NONE;
    }

    if(this->entity->pY >= (this->windowHeight-this->entity->imgHeight) || this->entity->pY <= 0)
    this->entity->vY *= -1;

    this->entity->txtPos.x = this->entity->pX  - (this->entity->txtWidth / 2) + (this->entity->imgWidth / 2);
    this->entity->txtPos.y = this->entity->pY - 20;

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
    
    SDL_Rect imgDstRect = {
        int(this->entity->pX),
        int(this->entity->pY),
        this->entity->imgWidth,
        this->entity->imgHeight
    };

    SDL_Rect txtDstRect = {
        int(this->entity->txtPos.x),
        int(this->entity->txtPos.y),
        this->entity->txtWidth,
        this->entity->txtHeight
    };
    
    // Dibujar imagen
    
    SDL_RenderCopyEx(
        this->renderer,
        this->entity->imgTexture,
        &this->srcRect,
        &imgDstRect,
        this->entity->angle,
        NULL,
        this->entity->imgFlip
    );

    // Dibujar Texto

    SDL_RenderCopyEx(
        this->renderer,
        this->entity->txtTexture,
        NULL, // El null dibuja toda la textura
        &txtDstRect,
        this->entity->txtAngle,
        NULL,
        SDL_FLIP_NONE
    );


    SDL_RenderPresent(this->renderer);
}

