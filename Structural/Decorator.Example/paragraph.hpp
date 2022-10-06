#ifndef PARAGRAPH_H_
#define PARAGRAPH_H_

#include <iostream>
#include <memory>
#include <string>

class Paragraph
{
    std::string text_;

public:
    Paragraph(const std::string& initial_text)
        : text_(initial_text)
    {
    }

    virtual ~Paragraph() = default;

    virtual std::string getHTML() const
    {
        return text_;
    }
};

class BoldParagraph : public Paragraph
{
protected:
    std::shared_ptr<Paragraph> wrapped_paragraph_;

public:
    BoldParagraph(std::shared_ptr<Paragraph> paragraph)
        : Paragraph("")
        , wrapped_paragraph_(paragraph)
    {
    }

    std::string getHTML() const override
    {
        return "<strong>" + wrapped_paragraph_->getHTML() + "</strong>";
    }
};

class ItalicParagraph : public Paragraph
{
protected:
    std::shared_ptr<Paragraph> wrapped_paragraph_;

public:
    ItalicParagraph(std::shared_ptr<Paragraph> paragraph)
        : Paragraph("")
        , wrapped_paragraph_(paragraph)
    {
    }

    std::string getHTML() const override
    {
        return "<i>" + wrapped_paragraph_->getHTML() + "</i>";
    }
};

#endif /*PARAGRAPH_H_*/
