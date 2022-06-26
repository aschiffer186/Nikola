#include "InputStream.hh"

namespace Nikola::FrontEnd::Lexer::_detail {
    
    InputStream::InputStream(const std::istream& inputStream)
    : M_buff{inputStream.rdbuf()}, M_iter{inputStream.rdbuf()}, M_line{1}, M_col{1}
    {

    }

    char InputStream::operator*()
    {
        if (M_iter == END)
            return NIKOLA_EOF;
        return *M_iter;
    }

    InputStream& InputStream::operator++()
    {
        advance();
        return *this;
    }

    char InputStream::lookahead()
    {
        char c = M_buff->snextc();
        M_buff->sungetc();
        return c;
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
            if (M_iter == END)
                return;
            ++M_iter;
            ++M_col;
            if (*M_iter == '\n')
            {
                M_col = 1;
                ++M_line;
                ++M_iter;
            }
            if (!isspace(*M_iter))
                return;
        }
    }
}