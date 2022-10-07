#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <string>

class Document
{
    std::string text_;

public:
    class Memento
    {
    private:
        std::string snapshot_;

        friend class Document;
    };

    Document() : text_{}
    {
    }

    Document(const std::string& text) : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }

    size_t length() const
    {
        return text_.size();
    }

    void add_text(const std::string& txt)
    {
        text_ += txt;
    }

    void to_upper()
    {
        boost::to_upper(text_);
    }

    void to_lower()
    {
        boost::to_lower(text_);
    }

    void clear()
    {
        text_.clear();
    }

    Memento create_memento() const
    {
        std::stringstream stream;
        boost::archive::text_oarchive archive(stream);
        archive << text_;

        Memento memento;
        memento.snapshot_ = stream.str();

        return memento;
    }

    void set_memento(Memento& memento)
    {
        std::stringstream stream{memento.snapshot_};
        boost::archive::text_iarchive archive(stream);
        archive >> text_;
    }

    void replace(size_t start_pos, size_t count, const std::string& text)
    {
        text_.replace(start_pos, count, text);
    }
};

#endif
