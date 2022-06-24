#ifndef INPUT_STREAM_HH
#define INPUT_STREAM_HH

#include <istream>
#include <iterator>
#include <string>

namespace Nikola::FrontEnd::Lexer
{
    /**
     * @brief Abstraction of a Nikola input source
     * 
     * The InputStream class encapsulates a stream of characters 
     * in a Nikola source and provides the ability to advance the 
     * position in the input stream, access the current character safely, 
     * access the next character safely, and obtain information about the position 
     * within the character stream.
     * 
     * @tparam _CharTp the character type stored in the input stream
     * @tparam Traits the traits type for _CharTpS
     */
    template<typename _CharTp, typename Traits = std::char_traits<_CharTp>>
    class InputStream 
    {
    private:
        using PosType = typename Traits::off_type;
    public:
        static constexpr _CharTp NIKOLA_EOF = Traits::();
    public:
        /**
         * @brief Construct a new Input Stream object
         * 
         * Creates an InputStream that encapsulates the specified 
         * input stream (represented as a std::istream).
         * 
         * @pre the inputStream is open and non in an error-state
         * @param inputStream the input stream to be encapsulated by *this
         */
        explicit InputStream(std::basic_istream<_CharTp, Traits>& inputStream)
        : M_iter{inputStream.rdbuf()}, M_line{1}, M_col{1}
        {

        }

        /**
         * @brief Returns the current character
         * 
         * Returns the current character in the input stream or 
         * NIKOLA_EOF if at the end of the input stream.
         * 
         * @return _CharTp the current character
         */
        _CharTp operator*()
        {
            if (M_iter == END)
                return NIKOLA_EOF;
            return *M_iter;
        }

        /**
         * @brief Advances the position in the input stream
         * 
         * Advances *this to the next non-whitespace, non-comment 
         * character unelss *this is at the end of the input stream.
         * In that case, this function does nothing. 
         * 
         * @return InputStream& 
         */
        InputStream& operator++()
        {
            advance();
            return *this;
        }

        /**
         * @brief Returns the lookahead character
         * 
         * Returns the next character or NIKOLA_EOF if 
         * the next character is at or past the end of the input stream.
         * 
         * @return _CharTp the lookahead character
         */
        _CharTp lookahead() const
        {
            auto it = std::next(M_iter);
            if (it == END)
                return NIKOLA_EOF;
            return *it;
        }

        /**
         * @brief Returns the current column
         * 
         * Return the current column (one-based) in the input stream.
         * 
         * @return PosType the current column 
         */
        constexpr PosType getCol() const
        {
            return M_col;
        }

        /**
         * @brief Returns the current line
         * 
         * Return the current line (one-based) in the input stream.
         * 
         * @return PosType the current line
         */
        constexpr PosType getLine() const 
        {
            return M_line;
        }
    private:
        void advance();
    private:
        template<typename _Tp, typename _Traits = std::char_traits<_Tp>>
        friend bool operator==(const InputStream<_Tp, _Traits>& lhs, const InputStream<_Tp, _Traits>& rhs);
        
        template<typename _Tp, typename _Traits = std::char_traits<_Tp>>
        friend bool operator!=(const InputStream<_Tp, _Traits>& lhs, const InputStream<_Tp, _Traits>& rhs);
    private:
        static const std::istreambuf_iterator<_CharTp, Traits> END;
    private:
        std::istreambuf_iterator<_CharTp, Traits> M_iter;
        PosType M_line;
        PosType M_col;
    };
}

#endif