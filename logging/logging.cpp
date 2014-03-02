#include "logging.h"

#include <ctime>
#include <iostream>

Logger logging;

Logger::Logger()
{
}

void Logger::addOutput(std::shared_ptr<LoggingOutput> output)
{
    outputs.insert(output);
}

void Logger::pushStatus(const std::string &msg)
{
    info_stack.push_back(msg);
}

void Logger::error(const char *format, ...)
{
    static char buf[2048];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, 2048, format, ap);
    va_end(ap);
    std::string msg(buf);
    std::set<std::shared_ptr<LoggingOutput> >::iterator it = outputs.begin();
    for(; it != outputs.end(); ++it)
        (*it)->log(50, info_stack, msg);
}

void Logger::logC(unsigned int level, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    logV(true, level, format, ap);
    va_end(ap);
}

void Logger::log(unsigned int level, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    logV(false, level, format, ap);
    va_end(ap);
}

void Logger::logC(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    logV(true, 10, format, ap);
    va_end(ap);
}

void Logger::log(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    logV(false, 10, format, ap);
    va_end(ap);
}

void Logger::logV(bool add_context, unsigned int level,
                  const char *format, va_list args)
{
    static char buf[2048];
    vsnprintf(buf, 2048, format, args);
    std::string msg(buf);
    std::set<std::shared_ptr<LoggingOutput> >::iterator it = outputs.begin();
    if(add_context)
    {
        for(; it != outputs.end(); ++it)
            (*it)->log(level, info_stack, msg);
    }
    else
    {
        for(; it != outputs.end(); ++it)
            (*it)->log(level, msg);
    }
}

void Logger::popStatus()
{
    info_stack.pop_back();
}

LoggingLevelFilter::LoggingLevelFilter(unsigned int minlevel,
                                       std::shared_ptr<LoggingOutput> filtered)
  : level(minlevel), output(filtered)
{
}

LoggingLevelFilter::~LoggingLevelFilter()
{
}

void LoggingLevelFilter::log(unsigned int level,
                             const std::vector<std::string> &infoStack,
                             const std::string &msg)
{
    output->log(level, infoStack, msg);
}

void LoggingLevelFilter::log(unsigned int level, const std::string &msg)
{
    output->log(level, msg);
}

FileOutput::FileOutput(const char *filename, bool append)
  : m_File(filename,
           std::ios::out |
           std::ios::binary |
           (append?std::ios::app:std::ios::trunc)),
    m_bWritten(false)
{
}

FileOutput::~FileOutput()
{
    if(m_bWritten)
        writeFooter();
}

void FileOutput::writeHeader()
{
    m_File << "log opened " << date() << "\n";
    m_bWritten = true;
}

void FileOutput::writeFooter()
{
    m_File << "--------------------\n";
    m_File << "log closed " << date() << "\n";
}

std::string FileOutput::date()
{
    char buf[20];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buf);
}

void FileOutput::log(unsigned int level,
                     const std::vector<std::string> &infoStack,
                     const std::string &msg)
{
    if(!m_bWritten)
        writeHeader();
    std::string d = date();
    m_File << "--------------------\n";
    std::vector<std::string>::const_iterator it = infoStack.begin();
    for(; it != infoStack.end(); ++it)
        m_File << d << "  : " << *it << "\n";
    m_File << d << " " << level << ": " << msg << "\n";
    m_File.flush();
}

void FileOutput::log(unsigned int level, const std::string &msg)
{
    if(!m_bWritten)
        writeHeader();
    m_File << "--------------------\n";
    m_File << date() << " " << level << ": " << msg << "\n";
    m_File.flush();
}

void ConsoleOutput::log(unsigned int level,
                        const std::vector<std::string> &infoStack,
                        const std::string &msg)
{
    std::cerr << "--------------------\n";
    std::vector<std::string>::const_iterator it = infoStack.begin();
    for(; it != infoStack.end(); ++it)
        std::cerr << " : " << *it << "\n";
    std::cerr << level << ": " << msg << "\n";
    std::cerr.flush();
}

void ConsoleOutput::log(unsigned int level, const std::string &msg)
{
    std::cerr << "--------------------\n";
    std::cerr << level << ": " << msg << "\n";
    std::cerr.flush();
}
