#ifndef LOGGING_H
#define LOGGING_H

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class LoggingOutput;

/**
 * Main class.
 *
 * A logger is what you write log to. It's also what you add outputs on.
 */
class Logger {

public:
    Logger();

    /**
     * Adds an output for the logging system.
     */
    void addOutput(std::shared_ptr<LoggingOutput> output);

    /**
     * Push a status string on the info stack.
     *
     * This message will only be shown as context if an error occurs.
     */
    void pushStatus(const std::string &msg);

    /**
     * Triggers an error (level 50).
     *
     * The error message will be logged, as well as the whole info stack for
     * context.
     */
    void error(const char *format, ...);

    /**
     * Logs a message.
     *
     * @param add_context If true, the info stack will be logged as well.
     * @param level The level of the message, simply passed to outputs.
     */
    void logC(unsigned int level, const char *format, ...);

    /**
     * Logs a message without context.
     *
     * @param level The level of the message, simply passed to outputs.
     */
    void log(unsigned int level, const char *format, ...);

    /**
     * Logs a message with level 10.
     *
     * @param add_context If true, the info stack will be logged as well.
     */
    void logC(const char *format, ...);

    /**
     * Logs a message with level 10 and no context.
     */
    void log(const char *format, ...);

    void logV(bool add_context, unsigned int level,
             const char *format, va_list args);

    void popStatus();

private:
    std::vector<std::string> info_stack;
    std::set<std::shared_ptr<LoggingOutput> > outputs;

};

/**
 * The default logger.
 *
 * This is a logger that is created automatically, so you can use it without
 * having to configure much.
 */
extern Logger logging;

/**
 * This objects adds context on the info stack of a logger.
 *
 * Create one object of this type is some scope; the info will be removed from
 * the stack when the object goes out of scope.
 */
class LoggingContext {

private:
    Logger &logger;

public:
    inline LoggingContext(Logger &log, const std::string &msg)
      : logger(log)
    {
        logger.pushStatus(msg);
    }

    inline LoggingContext(const std::string &msg)
      : logger(logging)
    {
        logging.pushStatus(msg);
    }

    inline LoggingContext(Logger &log, const char *format, ...)
      : logger(log)
    {
        static char buf[2048];
        va_list ap;
        va_start(ap, format);
        vsnprintf(buf, 2048, format, ap);
        va_end(ap);
        logger.pushStatus(buf);
    }

    inline LoggingContext(const char *format, ...)
      : logger(logging)
    {
        static char buf[2048];
        va_list ap;
        va_start(ap, format);
        vsnprintf(buf, 2048, format, ap);
        va_end(ap);
        logging.pushStatus(buf);
    }
    
    inline ~LoggingContext()
    {
        logger.popStatus();
    }

};

/**
 * Interface for the outputs.
 *
 * Implement this class to provide an alternative sink for logging messages.
 */
class LoggingOutput {

public:
    virtual ~LoggingOutput() {}

    virtual void log(unsigned int level,
                     const std::vector<std::string> &infoStack,
                     const std::string &msg) = 0;
    virtual void log(unsigned int level,
                     const std::string &msg) = 0;

};

/**
 * This is a filter that discards messages above a given priority level.
 */
class LoggingLevelFilter : public LoggingOutput {

private:
    unsigned int level;
    std::shared_ptr<LoggingOutput> output;

public:
    LoggingLevelFilter(unsigned int minlevel,
                       std::shared_ptr<LoggingOutput> filtered);
    ~LoggingLevelFilter();

    void log(unsigned int level,
             const std::vector<std::string> &infoStack,
             const std::string &msg);
    void log(unsigned int level,
             const std::string &msg);

};

/**
 * This output writes every line to a file.
 *
 * The file is flushed after each new message, so it is not very fast; but you
 * are sure not to lose entries on application crash.
 */
class FileOutput : public LoggingOutput {

private:
    std::ofstream m_File;
    bool m_bWritten;

private:
    void writeHeader();
    void writeFooter();
    std::string date();

public:
    FileOutput(const char *filename, bool append=false);
    ~FileOutput();

    void log(unsigned int level,
             const std::vector<std::string> &infoStack,
             const std::string &msg);
    void log(unsigned int level,
             const std::string &msg);

};

/**
 * This output writes to stderr.
 */
class ConsoleOutput : public LoggingOutput {

public:
    void log(unsigned int level,
             const std::vector<std::string> &infoStack,
             const std::string &msg);
    void log(unsigned int level,
             const std::string &msg);

};

#endif
