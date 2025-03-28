#pragma once
#include "scriptInstance.h"
#include "../math/random.h"
namespace Engine
{
    struct PipeSpawner : ScriptInstance
    {
        ENGINE_INLINE void OnStart()
        {
            PlayMusic("music", -1, 5, 100);
        }
        ENGINE_INLINE void OnUpdate(float dt)
        {
            if(gameOver) return;

            //find player
            auto player = FindEntity("player");
            auto& playerRB = player.GetComponent<ECS::RigidbodyComponent>();
            if(player.IsAlive() && playerRB.disabled)
            {
                auto ground = FindEntity("ground");
                auto& grdRB = ground.GetComponent<ECS::RigidbodyComponent>();
                grdRB.disabled = true;

                //Game Over Text
                auto scr = FindEntity("score");
                auto& gameoverText = scr.GetComponent<ECS::TextComponent>();
                gameoverText.text = "GAME OVER";
                
                //stop pipe motion
                for(auto& pipe : pipes)
                {
                    auto& rb = pipe.GetComponent<ECS::RigidbodyComponent>();
                    rb.disabled = true;
                    auto& co = pipe.GetComponent<ECS::ColliderComponent>();
                    co.disabled = true;
                }

                gameOver = true;
                return;
            }

            UpdatePipes();

            if(time > 2.5f)
            {
                time = 0.f;
                float space = Math::Random(60,150);
                SpawnPipe(380, -space);
                SpawnPipe(380, 720/2 + space);
            }

            time += dt;
        }

        ENGINE_INLINE void SpawnPipe(float x, float y)
        {
            auto pipe = AddEntity();
            auto& pipeTr = pipe.GetComponent<ECS::TransformComponent>();
            pipeTr.translate = Vec2f(x,y);

            //RigidBody
            auto& pipeRB = pipe.AddComponent<ECS::RigidbodyComponent>();
            pipeRB.body.gravityScale = 0.f;
            pipeRB.body.velocity.x = -100.f;

            //Sprite
            auto pipeAsset = GetAsset<TextureAsset>("pipeSprite");
            auto& pipeSprite = pipe.AddComponent<ECS::SpriteComponent>();
            pipeSprite.flip = (y < 0) ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;
            pipeSprite.sprite = pipeAsset->id;

            //Collider
            auto& pipeCol = pipe.AddComponent<ECS::ColliderComponent>();
            pipeCol.collider = 
            {
                pipeTr.translate.x,
                pipeTr.translate.y,
                (float)pipeAsset->instance.width,
                (float)pipeAsset->instance.height
            };
            pipes.push_back(pipe);
        }

        ENGINE_INLINE void UpdatePipes()
        {
            auto it = pipes.begin();

            while( it != pipes.end())
            {
                auto& pipe = (*it);

                if(!pipe.IsAlive())
                {
                    it = pipes.erase(it);
                    continue;
                }

                //destroy if out of the screen and set score
                auto& pipeTr = pipe.GetComponent<ECS::TransformComponent>();
                if(pipeTr.translate.x < -50)
                {
                    pipe.Destroy();
                    auto& scoreText = FindEntity("score").GetComponent<ECS::TextComponent>();
                    scoreText.text = "Score: " + std::to_string(++score/2);
                }
                it++;
            }
        }
    private:
        std::vector<ECS::Entity> pipes;
        bool gameOver {false};
        float time {0.f};
        int score {0};
    };


}