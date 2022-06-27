#ifndef INPUT_STREAM_HH
#define INPUT_STREAM_HH

#include <istream>
#include <iterator>
#include <string>

///@file InputStream.hh
///Handles processing input to the Nikola compiler

namespace Nikola::FrontEnd::Lexer::_detail
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
     */
    class InputStream 
    {
    private:
        using PosType = std::char_traits<char>::off_type;
    public:
        static constexpr char NIKOLA_EOF = std::char_traits<char>::eof();
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
        explicit InputStream(const std::istream& inputStream);

        /**
         * @brief Returns the current character
         * 
         * Returns the current character in the input stream or 
         * NIKOLA_EOF if at the end of the input stream.
         * 
         * @return _CharTp the current character
         */
        char operator*();

        /**
         * @brief Advances the position in the input stream
         * 
         * Advances *this to the next non-whitespace, non-comment 
         * character unelss *this is at the end of the input stream.
         * In that case, this function does nothing. 
         * 
         * @return InputStream& 
         */
        InputStream& operator++();

        /**
         * @brief Returns the lookahead character
         * 
         * Returns the next character or NIKOLA_EOF if 
         * the next character is at or past the end of the input stream.
         * 
         * @return _CharTp the lookahead character
         */
        char lookahead();

        /**
         * @brief Returns the current column
         * 
         * Return the current column (one-based) in the input stream.
         * 
         * @return PosType the current column 
         */
        PosType getCol() const;

        /**
         * @brief Returns the current line
         * 
         * Return the current line (one-based) in the input stream.
         * 
         * @return PosType the current line
         */
        PosType getLine() const;
    private:
        //Implementation of operator++()
        void advance();
    private:
        static constexpr std::istreambuf_iterator<char, std::char_traits<char>> END{};
    private:
        std::basic_streambuf<char, std::char_traits<char>> *M_buff;
        std::istreambuf_iterator<char, std::char_traits<char>> M_iter;
        PosType M_line;
        PosType M_col;
    };
}

#endif