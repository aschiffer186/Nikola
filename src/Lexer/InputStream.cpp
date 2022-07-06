#include "InputStream.hh"

namespace Nikola::FrontEnd::Lexer::_detail {
    
    InputStream::InputStream(std::istream& inputStream)
    : M_curr{NIKOLA_EOF}, M_stream{inputStream}, M_col{1}, M_line{1}
    {

    }

    char InputStream::operator*()
    {
        return M_curr;
    }

    InputStream& InputStream::operator++()
    {
        advance();
        return *this;
    }

    char InputStream::lookahead()
    {
        return M_stream.peek();
    }

    InputStream::PosType InputStream::getCol() const
    {
        return M_col;
    }

    InputStream::PosType InputStream::getLine() const 
    {
        return M_line;
    }

    void InputStream::advance()
    {
        while(true)
        {
            if (M_stream.eof())
            {
                M_curr = NIKOLA_EOF;
                return;
            }
            M_curr = M_stream.get();
            ++M_col;
            if (M_curr == '\n')
            {
                M_col = 1;
                ++M_line;
                M_curr = M_stream.get();
            }
            if (!isspace(M_curr))
                return;
        }
    }

    InputStream::MarkerType InputStream::getPos() const
    {
        return M_stream.tellg();
    } 

    void InputStream::setPos(InputStream::MarkerType pos)
    {
        M_stream.seekg(pos);
    }
}