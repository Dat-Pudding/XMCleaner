#include <iostream>
#include <string>
#include <vector>

namespace Converters
{
    class ToCSV
    {
    public:
        void Convert(std::string);
    private:
        void BracketToSpace(std::string, int);
        void EqualiseSpaces(std::string, int);
        void SpaceToComma(std::string, int);
        void Polisher(std::string, int);
        void Emitter(std::string, int);
    };
};

int main()
{
    std::string input = "[21-12-2024 16:34:56:678] sensor1   speed(10s/60s/15m) 2377.7 2488.4 2322.2 RPM";

    Converters::ToCSV csvConverter;
    csvConverter.Convert(input);
    return 0;
}

void Converters::ToCSV::Convert(std::string line, int counter)
{
    int counter = 1;
    BracketToSpace(line, counter);
}

void Converters::ToCSV::BracketToSpace(std::string line, int counter)
{
    std::string lineCache = line;

    for (int i = 0; i < line.length(); ++i)
    {
        if (lineCache[i] == '[' || lineCache[i] == ']')
        {
            lineCache[i] = ' ';
        }
    }
    line = lineCache;
    std::cout << "After BTS: " << line << std::endl;
    EqualiseSpaces(line, counter);

// Should be 
// line = " 21-12-2024 16:34:56:678  sensor1   speed(10s/60s/15m) 2377.7 2488.4 2322.2 RPM";
// at this point
}

void Converters::ToCSV::EqualiseSpaces(std::string line, int counter)
{
    int prevPos = 0;
    int currentPos = 1;
    char filterMask = ' ';
    std::string lineCache = line;
    
    while (lineCache[currentPos] != '\0')
    {
        if (lineCache[prevPos] == filterMask && lineCache[currentPos] == filterMask)
        {
            int newPos = currentPos;
            
            while (newPos <= lineCache.length() - 1)
            {
                lineCache[newPos] = lineCache[newPos + 1];
                ++newPos;
                lineCache.shrink_to_fit();
                line = lineCache;
            }
        }
        else
        {
            ++currentPos;
            ++prevPos;
        }
    }
    
    line = lineCache;
    std::cout << "After ES: " << line << std::endl;
    SpaceToComma(line, counter);

// Should be
// line = " 21-12-2024 16:34:56:678 sensor1 speed(10s/60s/15m) 2377.7 2488.4 2322.2 RPM";
// at this point
}

void Converters::ToCSV::SpaceToComma(std::string line, int counter)
{
    std::string lineCache = line;

    for (int i = 0; i < line.length(); ++i)
    {
        if (lineCache[i] == ' ')
        {
            lineCache[i] = ',';
        }
    }

    line = lineCache;
    std::cout << "After STC: " << line << std::endl;
    Polisher(line, counter);

// Should be 
// line = ",21-12-2024,16:34:56:678,sensor1,speed(10s/60s/15m),2377.7,2488.4,2322.2,RPM";
// at this point
}

void Converters::ToCSV::Polisher(std::string line, int counter)
{
    char filterMask[4] = { ',' , 'R', 'P', 'M' };
    std::string lineCache = line;
    
     for (int i = 0; i < line.length(); ++i)
    {
        switch (i)
        {
            case 0:
            {
                auto lcStart = lineCache.begin();
                lineCache.erase(lcStart);
                lineCache.shrink_to_fit();
                line = lineCache;
                
                std::cout << "After P1: " << line << std::endl;
                continue;
            }

// Should be 
// lineCache = "21-12-2024,16:34:56:678,sensor1,speed(10s/60s/15m),2377.7,2488.4,2322.2,RPM";
// at this point

// ============================
// case 31 should be "," of the ",speed(10s/60s/15m)" 
// since the entire section is to be removed in
// lineCach[] it will advance int newPos only as often
// as the target string is long

            case 31:
            {
                std::string filterPhrase = ",speed(10s/60s/15m)";
                
                auto start = lineCache.begin() + i;
                auto last = start + filterPhrase.length();
                lineCache.erase(start, last);
                lineCache.shrink_to_fit();
                line = lineCache;
         
                std::cout << "After P2: " << line << std::endl;
                continue;
            }
// Should be 
// lineCache = "21-12-2024,16:34:56:678,sensor1,2377.7,2488.4,2322.2,RPM";
// at this point

// ============================
// case 51 should be "," of the suffix ",RPM" 
// since another inputMask candidate will be moved to
// lineCach[51] it will only ever advance int pos 
// when nothing was changed

            case 52:
            {
                auto first = lineCache.begin() + i;
                auto last = lineCache.end();
                lineCache.erase(first, last);
;
                lineCache.shrink_to_fit();
                line = lineCache;
                 
                std::cout << "After P3: " << line << std::endl;
                continue;
            }

// Should be 
// lineCache = "21-12-2024,16:34:56:678,sensor1,2377.7,2488.4,2322.2";
// at this point

            default:
            {
                ++i;
                continue;
            }
        }
    }
    line = lineCache;
    Emitter(line, counter);

// Should be 
// line = "21-12-2024,16:34:56:678,sensor1,2377.7,2488.4,2322.2";
// at this point
}

void Converters::ToCSV::Emitter(std::string line, int counter)
{
    std::cout << "Converted line [#" << counter << "]" << std::endl;
    std::cout << "Result: \n" << line << std::endl;
    std::cout << "Expected: \n21-12-2024,16:34:56:678,sensor1,2377.7,2488.4,2322.2" << std::endl;
    return;
}