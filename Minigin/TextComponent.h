#pragma once
#include "Component.h"

namespace dae {
    class Font;
    class Texture2D;
    class TextComponent : public Component
    {
    public:
        TextComponent(const std::string& text, const std::shared_ptr<Font>& font);

        void Update() override;
        void Render() const override;
        void SetText(const std::string& text);
        
    private:
        bool m_NeedsUpdate;
        std::string m_Text;
        std::shared_ptr<Font> m_Font;
        std::shared_ptr<Texture2D> m_TextTexture;
    };
}