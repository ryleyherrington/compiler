/**
 * @file main.cpp
 *
 * The entry point for our compiler.
 * 
 * @author Dan Albert <dan@gingerhq.net>
 *
 * This compiler translates from IBTL (Itty Bitty Teaching Language) to Gforth.
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"
#include "gforth_code_generator.h"
#include "messages.h"
#include "syntax_tree.h"
 
/**
 * @def MIN
 *
 * Returns the minimum of two values.
 *
 * @param a The first value.
 * @param b The second value.
 *
 * @return The minimum of the two values.
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @def MAX
 *
 * Returns the maximum of two values.
 *
 * @param a The first value.
 * @param b The second value.
 *
 * @return The maximum of the two values.
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * @def CLAMP
 *
 * Returns a value that is clamped between two values.
 *
 * @param x The value to be clamped.
 * @param l The lower bound that x is to be clamped to.
 * @param h The upper bound that x is to be clamped to.
 *
 * @return l if x < l, h if x > h, x otherwise.
 */
#define CLAMP(x, l, h) (((x) > (h)) ? (h) : (((x) < (l)) ? (l) : (x)))

#define DEFAULT_MODE Mode::Translate

/**
 * Translates a source file.
 *
 * @param file The file to be translated.
 */
void translate(const char* file);

/**
 * Scans a file and prints the list of tokens.
 *
 * @param file The file to be scanned.
 */
void printScan(const char* file);

/**
 * Parses a file and prints the generated syntax tree.
 *
 * @param file The file to be parsed.
 */
void printParse(const char* file);

/**
 * Parses a file and prints the semantically analyzed syntax tree.
 *
 * @param file The file to be parsed.
 */
void printSemantic(const char* file);

/**
 * Prints usage information.
 */
void usage(void);

enum class Mode
{
	Scan,
	Parse,
	Semantic,
	Symbol,
	Translate
};

int main(int argc, char **argv)
{
	Mode mode = DEFAULT_MODE;
	int c;
 
	while (1)
	{
		static struct option long_options[] =
		{
			{"help",     no_argument, 0, 'h'},
			{"tokenize", no_argument, 0, 't'},
			{"parse",    no_argument, 0, 'p'},
			{"semantic", no_argument, 0, 's'},
			{"symbol",   no_argument, 0, 'S'},
			{"verbose",  no_argument, 0, 'v'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
 
		c = getopt_long(argc, argv, "htpsSv",
		                long_options, &option_index);
 
		/* Detect the end of the options. */
		if (c == -1)
			break;
 
		switch (c)
		{
		case 0:
			/* If this option set a flag, do nothing else now. */
			if (long_options[option_index].flag != 0)
				break;
			printf ("option %s", long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf ("\n");
			break;
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
			break;
		case 't':
			mode = Mode::Scan;
			break;
		case 'p':
			mode = Mode::Parse;
			break;
		case 's':
			mode = Mode::Semantic;
			break;
		case 'v':
			set_log_level(CLAMP(get_log_level() + 1,
			                    LOGLEVEL_MIN, LOGLEVEL_MAX));
			break;
		case '?':
			/* getopt_long already printed an error message. */
			break;
		default:
			CRITICAL("Should never reach default case");
			exit(EXIT_FAILURE);
			break;
		}
	}
 
	if (optind < argc)
	{
		while (optind < argc)
		{
			char* file = argv[optind++];
			switch (mode)
			{
			case Mode::Scan:
				printScan(file);
				break;
			case Mode::Parse:
				printParse(file);
				break;
			case Mode::Semantic:
				printSemantic(file);
				break;
			case Mode::Translate:
				translate(file);
				break;
			default:
				CRITICAL("invalid mode %d", static_cast<int>(mode));
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		usage();
		exit(EXIT_FAILURE);
	}
 
	return 0;
}

void translate(const char* file)
{
	assert(file);
	INFO("translating %s", file);
	Parser parser(file);
	parser.ParseTree();
	SemanticAnalyzer sem(parser.GetTree());
	sem.Construct();

	GforthCodeGenerator generator(sem.GetTree());
	generator.Synthesize();
}

void printScan(const char* file)
{
	assert(file);
	INFO("scanning %s", file);

	Lexer lex;
	if (!lex.Init(file))
	{
		CRITICAL("Could not open file %s", file);
		exit(EXIT_FAILURE);
	}

	while (lex.HasNext())
	{
		lex.Next().Print();
		printf("\n");
	}
}

void printParse(const char* file)
{
	assert(file);
	INFO("parsing %s", file);
	Parser parser(file);
	parser.ParseTree();
	parser.PrintTree();
}

void printSemantic(const char* file)
{
	assert(file);
	INFO("parsing %s", file);
	Parser parser(file);
	parser.ParseTree();
	SemanticAnalyzer sem(parser.GetTree());
	sem.Construct();
	sem.PrintTree();
}

void usage(void)
{
    printf("usage: compiler OPTIONS FILES\n");
    printf("OPTIONS:\n");
    printf("    -h, --help      - display the message\n");
	printf("    -t, --tokenize  - print the scanned tokens and exit\n");
	printf("    -p, --parse  	- print the parse tree and exit\n");
	printf("    -s, --syntax    - print the parsed syntax tree and exit\n");
	printf("    -S, --symbol    - print the symbol table and  exit\n");
    printf("    -v, --verbose   - increase output verbosity\n");
}

