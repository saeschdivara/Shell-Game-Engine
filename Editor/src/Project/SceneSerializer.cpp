#include "SceneSerializer.h"

#include <Engine/Project/Entities/Components.h>
#include <Engine/Project/Entities/EntityManager.h>
#include <Engine/Project/Entities/SceneEntity.h>

#include <codecvt>
#include <fstream>
#include <yaml-cpp/yaml.h>

#define KEY_NAME            "Name"
#define KEY_ID              "ID"
#define KEY_ENTITIES        "Entities"
#define KEY_COMPONENTS      "Components"
#define KEY_CMP_TRANSFORM   "Transform"
#define KEY_TRANSLATION     "Translation"
#define KEY_ROTATION        "Rotation"
#define KEY_SCALE           "Scale"
#define KEY_CMP_SPRITE      "Sprite"
#define KEY_TEXTURE2D       "Texture2D"
#define KEY_COLOR           "Color"
#define KEY_CMP_SCRIPT      "Scripting"
#define KEY_PATH            "Path"
#define KEY_CLASS_NAME      "Class-Name"


namespace Shell::Editor {

    inline glm::vec3 ParseVec3(const std::string & input) {
        auto findFirstBar = input.find('|');
        auto findSecondBar = input.find('|', findFirstBar+1);
        return glm::vec3{
                std::stof(input.substr(0, findFirstBar)),
                std::stof(input.substr(findFirstBar+1, findSecondBar)),
                std::stof(input.substr(findSecondBar+1))
        };
    }

    inline glm::vec4 ParseVec4(const std::string & input) {
        auto findFirstBar = input.find('|');
        auto findSecondBar = input.find('|', findFirstBar+1);
        auto findThirdBar = input.find('|', findSecondBar+1);
        return glm::vec4{
                std::stof(input.substr(0, findFirstBar)),
                std::stof(input.substr(findFirstBar+1, findSecondBar)),
                std::stof(input.substr(findSecondBar+1, findThirdBar)),
                std::stof(input.substr(findThirdBar+1))
        };
    }

    inline YAML::Emitter& operator<<(YAML::Emitter& emitter, glm::vec3 & vec3) {
        emitter << std::to_string(vec3.x) + "|" + std::to_string(vec3.y) + "|" + std::to_string(vec3.z);
        return emitter;
    }

    inline YAML::Emitter& operator<<(YAML::Emitter& emitter, glm::vec4 & vec4) {
        emitter << std::to_string(vec4.r) + "|" + std::to_string(vec4.g) + "|" + std::to_string(vec4.b) + "|" + std::to_string(vec4.a);
        return emitter;
    }

    inline YAML::Emitter& operator<<(YAML::Emitter& emitter, SceneEntity * entity) {

        emitter << YAML::BeginMap;

        emitter << YAML::Key << KEY_NAME;
        emitter << YAML::Value << entity->GetName();

        emitter << YAML::Key << KEY_ID;
        emitter << YAML::Value << UuidToString(entity->GetUuid());

        emitter << YAML::Key << KEY_COMPONENTS;
        emitter << YAML::Value;

        emitter << YAML::BeginMap;

        if (EntityManager::Instance()->HasComponent<TransformComponent>(entity)) {
            auto transformCmp = EntityManager::Instance()->GetComponent<TransformComponent>(entity);
            emitter << YAML::Key << KEY_CMP_TRANSFORM;
            emitter << YAML::Value;

            emitter << YAML::BeginMap;
            emitter << YAML::Key << KEY_TRANSLATION;
            emitter << YAML::Value << transformCmp.Translation;
            emitter << YAML::Key << KEY_ROTATION;
            emitter << YAML::Value << transformCmp.Rotation;
            emitter << YAML::Key << KEY_SCALE;
            emitter << YAML::Value << transformCmp.Scale;
            emitter << YAML::EndMap;
        }

        if (EntityManager::Instance()->HasComponent<SpriteComponent>(entity)) {
            auto spriteCmp = EntityManager::Instance()->GetComponent<SpriteComponent>(entity);
            emitter << YAML::Key << KEY_CMP_SPRITE;
            emitter << YAML::Value;

            emitter << YAML::BeginMap;

            // store either color or texture
            if (spriteCmp.Texture) {
                emitter << YAML::Key << KEY_TEXTURE2D;
                emitter << YAML::Value << spriteCmp.Texture->GetPath();
            } else {
                emitter << YAML::Key << KEY_COLOR;
                emitter << YAML::Value << spriteCmp.Color;
            }

            emitter << YAML::EndMap;
        }

        if (EntityManager::Instance()->HasComponent<ScriptingComponent>(entity)) {
            auto scriptingCmp = EntityManager::Instance()->GetComponent<ScriptingComponent>(entity);
            emitter << YAML::Key << KEY_CMP_SCRIPT;
            emitter << YAML::Value;

            emitter << YAML::BeginMap;

            emitter << YAML::Key << KEY_PATH;
            emitter << YAML::Value << scriptingCmp.Path;

            emitter << YAML::Key << KEY_CLASS_NAME;
            emitter << YAML::Value << scriptingCmp.ClassName;

            emitter << YAML::EndMap;
        }

        emitter << YAML::EndMap;

        if (entity->HasChildren()) {
            emitter << YAML::Key << "Children";
            emitter << YAML::BeginSeq;

            for (const auto &childEntity: entity->GetChildren()) {
                emitter << childEntity;
            }

            emitter << YAML::EndSeq;
        }

        emitter << YAML::EndMap;

        return emitter;
    }

    void SceneSerializer::SerializeToFile(const std::filesystem::path &path, const Ref<SceneBlueprint>& sceneBlueprint) {

        YAML::Emitter out;
        out << YAML::Comment("This file is automatically generated by the editor, do not modify it!");
        out << YAML::BeginMap;

        out << YAML::Key << KEY_NAME;
        out << YAML::Value << sceneBlueprint->GetName();

        out << YAML::Key << KEY_ID;
        out << YAML::Value << UuidToString(sceneBlueprint->GetUuid());

        out << YAML::Key << KEY_ENTITIES;
        out << YAML::Value;

        out << YAML::BeginSeq;

        for (const auto &entity: sceneBlueprint->GetEntityTree()) {
            out << entity;
        }

        out << YAML::EndSeq;

        out << YAML::EndMap;

        std::ofstream projectFile(path);
        projectFile << out.c_str();
    }

    Ref <SceneBlueprint> SceneSerializer::DeserializeFromFile(const std::filesystem::path &path) {
        SHELL_INFO("Try loading scene");
        YAML::Node config = YAML::LoadFile(path.generic_string());

        if (!config[KEY_NAME]) {
            SHELL_WARN("Could not read {0} from scene file", KEY_NAME);
            return nullptr;
        }

        if (!config[KEY_ID]) {
            SHELL_WARN("Could not read {0} from scene file", KEY_ID);
            return nullptr;
        }

        if (!config[KEY_ENTITIES]) {
            SHELL_WARN("Could not read {0} from scene file", KEY_ENTITIES);
            return nullptr;
        }

        auto sceneName = config[KEY_NAME].as<std::string>();
        auto sceneID = Uuid::Create(config[KEY_ID].as<std::string>());
        auto bluePrint = CreateRef<SceneBlueprint>(sceneName, sceneID);

        auto entities = config[KEY_ENTITIES];
        for(YAML::const_iterator it = entities.begin(); it != entities.end(); ++it) {
            auto entity = it->as<YAML::Node>();

            if (!entity[KEY_NAME]) {
                SHELL_WARN("Could not read {0} from scene entity", KEY_NAME);
                return nullptr;
            }

            if (!entity[KEY_ID]) {
                SHELL_WARN("Could not read {0} from scene entity", KEY_ID);
                return nullptr;
            }

            auto entityName = entity[KEY_NAME].as<std::string>();
            auto entityID = Uuid::Create(entity[KEY_ID].as<std::string>());
            SceneEntity * sceneEntity = EntityManager::Instance()->CreateEmptyEntity(bluePrint, entityName, entityID);
            bluePrint->AddEntity(sceneEntity);

            auto componentsNode = entity[KEY_COMPONENTS];
            if (componentsNode) {
                for(YAML::const_iterator componentIterator = componentsNode.begin(); componentIterator != componentsNode.end(); ++componentIterator) {
                    auto componentKey = componentIterator->first.as<std::string>();

                    if (componentKey == KEY_CMP_TRANSFORM) {
                        auto transformCmpNode = componentsNode[KEY_CMP_TRANSFORM].as<YAML::Node>();
                        auto translation = ParseVec3(transformCmpNode[KEY_TRANSLATION].as<std::string>());
                        auto rotation = ParseVec3(transformCmpNode[KEY_ROTATION].as<std::string>());
                        auto scale = ParseVec3(transformCmpNode[KEY_SCALE].as<std::string>());

                        EntityManager::Instance()->AddComponent<TransformComponent>(sceneEntity, translation, rotation, scale);
                    }
                    else if (componentKey == KEY_CMP_SPRITE) {
                        auto spriteCmpNode = componentsNode[KEY_CMP_SPRITE].as<YAML::Node>();

                        if (spriteCmpNode[KEY_TEXTURE2D]) {
                            auto texturePath = spriteCmpNode[KEY_TEXTURE2D].as<std::string>();
                            auto texture = Texture2D::Create(texturePath);

                            EntityManager::Instance()->AddComponent<SpriteComponent>(sceneEntity, texture);
                        } else {
                            auto color = ParseVec4(spriteCmpNode[KEY_COLOR].as<std::string>());
                            EntityManager::Instance()->AddComponent<SpriteComponent>(sceneEntity, color);
                        }
                    }
                    else if (componentKey == KEY_CMP_SCRIPT) {
                        auto scriptingCmpNode = componentsNode[KEY_CMP_SCRIPT].as<YAML::Node>();
                        auto scriptPath = scriptingCmpNode[KEY_PATH].as<std::string>();
                        auto scriptClassName = scriptingCmpNode[KEY_CLASS_NAME].as<std::string>();

                        EntityManager::Instance()->AddComponent<ScriptingComponent>(sceneEntity, scriptPath, scriptClassName);
                    }
                }
            }
        }

        return bluePrint;
    }
}