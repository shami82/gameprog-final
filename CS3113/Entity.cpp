#include "Entity.h"

Entity::Entity() : mPosition {0.0f, 0.0f}, mMovement {0.0f, 0.0f}, 
                   mScale {DEFAULT_SIZE, DEFAULT_SIZE},
                   mColliderDimensions {DEFAULT_SIZE, DEFAULT_SIZE}, 
                   mTexture {}, mTextureType {SINGLE}, mAngle {0.0f},
                   mSpriteSheetDimensions {}, mDirection {RIGHT}, 
                   mAnimationAtlas {{}}, mAnimationIndices {}, mFrameSpeed {0},
                   mEntityType {NONE}, mSpeed {DEFAULT_SPEED} { }

Entity::Entity(Vector2 position, Vector2 scale, Texture2D texture, 
    EntityType entityType) : mPosition(position), 
    mScale(scale), mTexture(texture), mTextureType(SINGLE), 
    mSpriteSheetDimensions({1,1}), mAnimationAtlas(), mEntityType(entityType), 
    mAngle(0.0f), mSpeed {DEFAULT_SPEED} { }

Entity::Entity(Vector2 position, Vector2 scale, Texture2D texture, 
        EntityType entityType, Vector2 colliderOffset) : mPosition {position}, 
        mMovement {0.0f, 0.0f}, mScale {scale}, 
        mColliderDimensions {scale}, mColliderOffset {colliderOffset}, 
        mTexture {texture}, 
        mTextureType {SINGLE}, mDirection {RIGHT}, mAnimationAtlas {{}}, 
        mAnimationIndices {}, mFrameSpeed {0}, mSpeed {DEFAULT_SPEED}, 
        mAngle {0.0f}, mEntityType {entityType} { }

Entity::Entity(Vector2 position, Vector2 scale, Texture2D texture, 
        TextureType textureType, Vector2 spriteSheetDimensions, 
        std::map<Direction, std::vector<int>> animationAtlas, 
        EntityType entityType) 
        : mPosition {position}, mMovement { 0.0f, 0.0f }, mScale {scale},
        mColliderDimensions {scale}, mColliderOffset { 0.0f, 0.0f }, 
        mTexture {texture}, 
        mTextureType {ATLAS}, mSpriteSheetDimensions {spriteSheetDimensions},
        mAnimationAtlas {animationAtlas}, mDirection {RIGHT},
        mAnimationIndices {animationAtlas.at(RIGHT)}, 
        mFrameSpeed {DEFAULT_FRAME_SPEED}, mAngle { 0.0f }, 
        mSpeed { DEFAULT_SPEED }, mEntityType {entityType} { }

Entity::Entity(Vector2 position, Vector2 scale, Texture2D texture, 
        TextureType textureType, Vector2 spriteSheetDimensions, 
        std::map<Direction, std::vector<int>> animationAtlas, 
        EntityType entityType, Vector2 colliderOffset) 
        : mPosition {position}, mMovement { 0.0f, 0.0f }, mScale {scale},
        mColliderDimensions {scale}, mColliderOffset {colliderOffset}, 
        mTexture {texture}, 
        mTextureType {ATLAS}, mSpriteSheetDimensions {spriteSheetDimensions},
        mAnimationAtlas {animationAtlas}, mDirection {RIGHT},
        mAnimationIndices {animationAtlas.at(RIGHT)}, 
        mFrameSpeed {DEFAULT_FRAME_SPEED}, mAngle { 0.0f }, 
        mSpeed { DEFAULT_SPEED }, mEntityType {entityType} { }

Entity::~Entity() { UnloadTexture(mTexture); };

void Entity::checkCollisionY(Entity *collidableEntities, int collisionCheckCount)
{
    for (int i = 0; i < collisionCheckCount; i++){
        Entity* other = &collidableEntities[i];
        if (!isColliding(other)) continue;

        float yDist = mPosition.y - other->mPosition.y;
        float overlap = ((mColliderDimensions.y + other->mColliderDimensions.y) * 0.5f) - fabs(yDist);

        if (yDist > 0){
            mPosition.y += overlap;
            mIsCollidingTop = true;
        } 
        else{
            mPosition.y -= overlap;
            mIsCollidingBottom = true;
        }
    }
}

void Entity::checkCollisionX(Entity *collidableEntities, int collisionCheckCount)
{
    for (int i = 0; i < collisionCheckCount; i++){
        Entity* other = &collidableEntities[i];
        if (!isColliding(other)) continue;

        float xDist = mPosition.x - other->mPosition.x;
        float overlap = ((mColliderDimensions.x + other->mColliderDimensions.x) * 0.5f) - fabs(xDist);

        if (xDist > 0){
            mPosition.x += overlap;
            mIsCollidingLeft = true;
        } 
        else{
            mPosition.x -= overlap;
            mIsCollidingRight = true;
        }
    }
}

// bool Entity::isColliding(Entity *other) const 
// {
//     if (!other->isActive() || other == this) return false;

//     float xDistance = fabs(mPosition.x - other->getPosition().x) - 
//         ((mColliderDimensions.x + other->getColliderDimensions().x) / 2.0f);
//     float yDistance = fabs(mPosition.y - other->getPosition().y) - 
//         ((mColliderDimensions.y + other->getColliderDimensions().y) / 2.0f);

//     if (xDistance < 0.0f && yDistance < 0.0f) return true;

//     return false;
// }

bool Entity::isColliding(Entity* other) const
{
    if (!other || !other->isActive() || other == this)
        return false;

    float xDistance = fabs(mPosition.x - other->mPosition.x) -
               ((mColliderDimensions.x + other->mColliderDimensions.x) * 0.5f);

    float yDistance = fabs(mPosition.y - other->mPosition.y) -
               ((mColliderDimensions.y + other->mColliderDimensions.y) * 0.5f);

    return (xDistance < 0 && yDistance < 0);
}

void Entity::animate(float deltaTime)
{
    mAnimationIndices = mAnimationAtlas.at(mDirection);

    mAnimationTime += deltaTime;
    float framesPerSecond = 3.0f / mFrameSpeed; // slower animation

    if (mAnimationTime >= framesPerSecond)
    {
        mAnimationTime = 0.0f;

        mCurrentFrameIndex++;
        mCurrentFrameIndex %= mAnimationIndices.size();
    }
}

// CREATE A NEW UPDATE THAT WOULD CHECK EACH ONE
void Entity::update(float deltaTime, Entity *player, 
    Entity *collidableEntities, int collisionCheckCount)
{
    
    mPosition.x += mMovement.x * mSpeed * deltaTime;
    checkCollisionX(collidableEntities, collisionCheckCount);
    mPosition.y += mMovement.y * mSpeed * deltaTime;
    checkCollisionY(collidableEntities, collisionCheckCount);

    // no gravity or physics or accelerations
    return;
}

// this new update function lets the player not completely walk over entities 
// accepts a vector of entities since every entity is different
// has a soft overlap so that theres still interactions possible through collisions
void Entity::update(float deltaTime, Entity* player,
                    const std::vector<Entity*>& collidables, int count)
{
    resetColliderFlags();

    static constexpr float SOFT_OVERLAP = 10.0f; // so it can intersect just a smidge

    float deltaX = mMovement.x * mSpeed * deltaTime;
    mPosition.x += deltaX;

    for (int i = 0; i < count; i++){
        Entity* other = collidables[i];
        if (!other || !other->isActive() || other == this) continue;

        if (isColliding(other)){
            float d = mPosition.x - other->mPosition.x;
            float totalHalfWidth =
                (mColliderDimensions.x + other->mColliderDimensions.x) * 0.5f;

            float overlap = totalHalfWidth - fabsf(d);

            if (overlap > SOFT_OVERLAP){
                bool movingToward = (deltaX > 0 && d < 0) || (deltaX < 0 && d > 0);

                if (movingToward){
                    mPosition.x -= deltaX;
                }

                mIsCollidingLeft  = (d > 0);
                mIsCollidingRight = (d < 0);
            }
        }
    }

    float deltaY = mMovement.y * mSpeed * deltaTime;
    mPosition.y += deltaY;

    for (int i = 0; i < count; i++){
        Entity* other = collidables[i];
        if (!other || !other->isActive() || other == this) continue;

        if (isColliding(other)){
            float d = mPosition.y - other->mPosition.y;
            float totalHalfHeight =
                (mColliderDimensions.y + other->mColliderDimensions.y) * 0.5f;

            float overlap = totalHalfHeight - fabsf(d);

            if (overlap > SOFT_OVERLAP){
                bool movingToward = (deltaY > 0 && d < 0) || (deltaY < 0 && d > 0);

                if (movingToward){
                    mPosition.y -= deltaY;
                }

                mIsCollidingTop    = (d > 0);
                mIsCollidingBottom = (d < 0);
            }
        }
    }
}

void Entity::render()
{
    if(mEntityStatus == INACTIVE) return;

    Rectangle textureArea;

    switch (mTextureType)
    {
        case SINGLE:
            // Whole texture (UV coordinates)
            textureArea = {
                // top-left corner
                0.0f, 0.0f,

                // bottom-right corner (of texture)
                static_cast<float>(mTexture.width),
                static_cast<float>(mTexture.height)
            };
            break;
        case ATLAS:
            textureArea = getUVRectangle(
                &mTexture, 
                mAnimationIndices[mCurrentFrameIndex], 
                mSpriteSheetDimensions.x, 
                mSpriteSheetDimensions.y
            );
        
        default: break;
    }

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mScale.x),
        static_cast<float>(mScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        mTexture, 
        textureArea, destinationArea, originOffset,
        mAngle, WHITE
    );

    // displayCollider();
}

void Entity::displayCollider() 
{
    // draw the collision box
    Rectangle colliderBox = {
        mPosition.x - mColliderDimensions.x / 2.0f,  
        mPosition.y - mColliderDimensions.y / 2.0f,  
        mColliderDimensions.x,                        
        mColliderDimensions.y                        
    };

    DrawRectangleLines(
        colliderBox.x,      // Top-left X
        colliderBox.y,      // Top-left Y
        colliderBox.width,  // Width
        colliderBox.height, // Height
        GREEN               // Color
    );
}