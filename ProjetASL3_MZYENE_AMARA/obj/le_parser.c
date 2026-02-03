/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/le_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <getopt.h> 

extern int yylineno;
extern char* yytext;
int yylex();

int lineno = 1; // défini pour tree.c
Node *root = NULL; // racine de l'arbre

void yyerror(const char *s) {
    fprintf(stderr, "Erreur de syntaxe à la ligne %d: %s", yylineno, s);
    if (yytext) fprintf(stderr, " --> : '%s'", yytext);
    printf("\n");
}

void print_help() {
    printf("Usage: tpcas [OPTIONS]\n");
    printf("Options:\n");
    printf("  -t, --tree       Affiche l'arbre abstrait sur la sortie standard\n");
    printf("  -h, --help       Affiche cette aide et termine l'exécution\n");
}

#line 98 "obj/le_parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "le_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CHARACTER = 3,                  /* CHARACTER  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_STRUCT = 7,                     /* STRUCT  */
  YYSYMBOL_VOID = 8,                       /* VOID  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_ADDSUB = 13,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 14,                   /* DIVSTAR  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_ORDER = 18,                     /* ORDER  */
  YYSYMBOL_19_ = 19,                       /* '{'  */
  YYSYMBOL_20_ = 20,                       /* '}'  */
  YYSYMBOL_21_ = 21,                       /* ';'  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_Prog = 28,                      /* Prog  */
  YYSYMBOL_StructDecls = 29,               /* StructDecls  */
  YYSYMBOL_StructDecl = 30,                /* StructDecl  */
  YYSYMBOL_StructFields = 31,              /* StructFields  */
  YYSYMBOL_StructField = 32,               /* StructField  */
  YYSYMBOL_DeclVars = 33,                  /* DeclVars  */
  YYSYMBOL_Declarateurs = 34,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 35,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 36,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 37,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 38,                /* Parametres  */
  YYSYMBOL_ListTypVar = 39,                /* ListTypVar  */
  YYSYMBOL_Corps = 40,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 41,                /* SuiteInstr  */
  YYSYMBOL_Instr = 42,                     /* Instr  */
  YYSYMBOL_Exp = 43,                       /* Exp  */
  YYSYMBOL_TB = 44,                        /* TB  */
  YYSYMBOL_FB = 45,                        /* FB  */
  YYSYMBOL_M = 46,                         /* M  */
  YYSYMBOL_E = 47,                         /* E  */
  YYSYMBOL_T = 48,                         /* T  */
  YYSYMBOL_F = 49,                         /* F  */
  YYSYMBOL_Arguments = 50,                 /* Arguments  */
  YYSYMBOL_ListExp = 51                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      23,    24,     2,     2,    22,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,     2,    20,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    53,    53,    67,    72,    77,    81,    90,    95,   103,
     109,   121,   129,   139,   149,   155,   160,   170,   175,   183,
     192,   199,   209,   214,   222,   230,   243,   255,   260,   264,
     271,   278,   286,   293,   301,   307,   312,   321,   329,   336,
     340,   347,   351,   358,   362,   369,   373,   380,   384,   391,
     395,   401,   407,   408,   412,   416,   417,   430,   431,   435,
     440
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CHARACTER", "NUM",
  "IDENT", "TYPE", "STRUCT", "VOID", "IF", "ELSE", "RETURN", "WHILE",
  "ADDSUB", "DIVSTAR", "AND", "OR", "EQ", "ORDER", "'{'", "'}'", "';'",
  "','", "'('", "')'", "'='", "'!'", "$accept", "Prog", "StructDecls",
  "StructDecl", "StructFields", "StructField", "DeclVars", "Declarateurs",
  "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres", "ListTypVar",
  "Corps", "SuiteInstr", "Instr", "Exp", "TB", "FB", "M", "E", "T", "F",
  "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,    18,    38,    42,   -77,    53,   -77,    58,   -77,    68,
      27,    -2,    76,    84,    91,    39,   -77,    78,    93,    94,
      20,   -77,   -77,    62,    77,    64,    93,    79,    96,   -77,
      97,   -77,    66,    93,    82,   -77,   -77,   100,    71,   -77,
      69,    71,    77,   101,    86,   -77,    73,   -77,   -77,   102,
     -77,    85,    88,   -77,    87,    93,    93,    32,   -77,   -77,
     -77,   106,   -77,    57,    90,     9,    92,   -77,   -77,   -77,
     -77,   103,    16,    16,    16,   -77,   -77,    95,    16,   -77,
      16,    16,   -15,    99,   104,    98,   107,   105,   -77,    16,
      45,   -77,   108,   109,   110,    -5,    12,    16,   -77,    44,
     -77,    16,   -77,    16,    16,    16,    16,    16,    54,   -77,
     113,    16,   -77,    50,   111,   -77,    99,   104,    98,   107,
     105,   -77,    50,   -77,   108,   112,   -77,   -77,    50,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,    14,     4,     0,     1,     0,     3,     0,
       0,     0,     0,     0,     0,     2,    18,     0,     0,     0,
       0,     8,    16,     0,    16,     0,     0,     0,     0,    17,
      14,    19,     0,     0,     0,     7,    13,     0,     0,    11,
       0,     0,     0,     0,    28,     9,     0,     6,    15,     0,
      22,     0,    23,    12,     0,     0,     0,     0,    10,    25,
      20,     0,    21,     0,     0,     0,     0,    28,    26,    37,
      27,     0,    58,     0,     0,    54,    53,    55,     0,    35,
       0,     0,     0,    39,    41,    43,    45,    47,    49,     0,
       0,    24,    60,     0,    57,     0,     0,    58,    50,     0,
      51,     0,    34,     0,     0,     0,     0,     0,     0,    36,
       0,     0,    29,     0,     0,    52,    38,    40,    42,    44,
      46,    48,     0,    33,    59,    30,    56,    32,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   114,   -77,   116,   115,    -8,   -77,   122,
     -77,    89,   -77,   -77,    56,   -55,   -65,    24,    23,    25,
      22,    33,   -76,    31,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,     9,    23,    15,    16,
      17,    51,    52,    31,    57,    70,    92,    83,    84,    85,
      86,    87,    88,    93,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      82,   101,    98,    22,    25,   100,   102,     1,    95,    96,
      32,   101,    75,    76,    77,    99,   112,    10,    40,    75,
      76,    77,    78,     5,   108,    46,    18,    19,   101,    78,
      79,   121,    80,    18,    19,    81,   113,    63,     6,    80,
      34,    64,    81,    65,    66,    28,   124,    14,    25,     7,
      63,    67,    68,    69,    64,    63,    65,    66,   125,    64,
     101,    65,    66,    11,    67,   109,    69,   127,   115,    67,
     101,    69,    10,   129,    12,    13,    14,    49,   122,    50,
      72,    24,    73,    36,    37,    39,    37,    45,    37,    26,
      53,    37,    56,    13,    58,    37,    27,    30,    22,    33,
      38,    42,    41,    47,    43,    48,    55,    59,    91,    60,
      61,    62,    71,    74,   103,    89,   105,     8,    97,   107,
     106,   104,   128,    90,   101,   116,   117,   119,   114,   118,
      54,     0,   111,   110,   123,   126,    35,    29,     0,   120,
       0,     0,     0,     0,     0,    44
};

static const yytype_int16 yycheck[] =
{
      65,    16,    78,     5,    12,    81,    21,     7,    73,    74,
      18,    16,     3,     4,     5,    80,    21,    19,    26,     3,
       4,     5,    13,     5,    89,    33,     6,     7,    16,    13,
      21,   107,    23,     6,     7,    26,    24,     5,     0,    23,
      20,     9,    26,    11,    12,     6,   111,     8,    56,     7,
       5,    19,    20,    21,     9,     5,    11,    12,   113,     9,
      16,    11,    12,     5,    19,    20,    21,   122,    24,    19,
      16,    21,    19,   128,     6,     7,     8,     6,    24,     8,
      23,     5,    25,    21,    22,    21,    22,    21,    22,     5,
      21,    22,     6,     7,    21,    22,     5,    19,     5,     5,
      23,     5,    23,    21,     7,     5,     5,     5,     5,    24,
      22,    24,     6,    23,    15,    23,    18,     3,    23,    14,
      13,    17,    10,    67,    16,   101,   103,   105,    97,   104,
      41,    -1,    22,    24,    21,    24,    20,    15,    -1,   106,
      -1,    -1,    -1,    -1,    -1,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    28,    29,    30,     5,     0,     7,    30,    33,
      19,     5,     6,     7,     8,    35,    36,    37,     6,     7,
      31,    32,     5,    34,     5,    34,     5,     5,     6,    36,
      19,    40,    34,     5,    20,    32,    21,    22,    23,    21,
      34,    23,     5,     7,    33,    21,    34,    21,     5,     6,
       8,    38,    39,    21,    38,     5,     6,    41,    21,     5,
      24,    22,    24,     5,     9,    11,    12,    19,    20,    21,
      42,     6,    23,    25,    23,     3,     4,     5,    13,    21,
      23,    26,    43,    44,    45,    46,    47,    48,    49,    23,
      41,     5,    43,    50,    51,    43,    43,    23,    49,    43,
      49,    16,    21,    15,    17,    18,    13,    14,    43,    20,
      24,    22,    21,    24,    50,    24,    44,    45,    46,    47,
      48,    49,    24,    21,    43,    42,    24,    42,    10,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    29,    29,    30,    31,    31,    32,
      32,    33,    33,    33,    33,    34,    34,    35,    35,    36,
      37,    37,    38,    38,    39,    39,    40,    41,    41,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    49,    49,    49,    49,    50,    50,    51,
      51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     0,     6,     2,     1,     3,
       4,     4,     5,     4,     0,     3,     1,     2,     1,     2,
       5,     5,     1,     1,     4,     2,     4,     2,     0,     4,
       5,     7,     5,     5,     3,     2,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     2,     3,     1,     1,     1,     4,     1,     0,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: StructDecls DeclVars DeclFoncts  */
#line 53 "src/le_parser.y"
                                    {
        Node *tmp = makeNode(Programme, NULL);
        if ((yyvsp[-2].node)) addChild(tmp, (yyvsp[-2].node));
        if ((yyvsp[-1].node)) addChild(tmp, (yyvsp[-1].node));
        if ((yyvsp[0].node)) addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
        root = tmp;
    }
#line 1223 "obj/le_parser.c"
    break;

  case 3: /* StructDecls: StructDecls StructDecl  */
#line 67 "src/le_parser.y"
                             {
          Node *tmp = (yyvsp[-1].node) ? (yyvsp[-1].node) : makeNode(StructDecls, NULL);
          addChild(tmp, (yyvsp[0].node));
          (yyval.node) = tmp;
      }
#line 1233 "obj/le_parser.c"
    break;

  case 4: /* StructDecls: StructDecl  */
#line 72 "src/le_parser.y"
                 {
          Node *tmp = makeNode(StructDecls, NULL);
          addChild(tmp, (yyvsp[0].node));
          (yyval.node) = tmp;
      }
#line 1243 "obj/le_parser.c"
    break;

  case 5: /* StructDecls: %empty  */
#line 77 "src/le_parser.y"
      { (yyval.node) = NULL; }
#line 1249 "obj/le_parser.c"
    break;

  case 6: /* StructDecl: STRUCT IDENT '{' StructFields '}' ';'  */
#line 81 "src/le_parser.y"
                                          {
        Node *tmp = makeNode(StructDecl, NULL);
        addChild(tmp, makeNode(id, (yyvsp[-4].id)));  // nom de la structure
        addChild(tmp, (yyvsp[-2].node));                // champs de la structure
        (yyval.node) = tmp;
    }
#line 1260 "obj/le_parser.c"
    break;

  case 7: /* StructFields: StructFields StructField  */
#line 90 "src/le_parser.y"
                               {
          Node *tmp = (yyvsp[-1].node) ? (yyvsp[-1].node) : makeNode(StructFields, NULL);
          addChild(tmp, (yyvsp[0].node));
          (yyval.node) = tmp;
      }
#line 1270 "obj/le_parser.c"
    break;

  case 8: /* StructFields: StructField  */
#line 95 "src/le_parser.y"
                  {
          Node *tmp = makeNode(StructFields, NULL);
          addChild(tmp, (yyvsp[0].node));
          (yyval.node) = tmp;
      }
#line 1280 "obj/le_parser.c"
    break;

  case 9: /* StructField: TYPE Declarateurs ';'  */
#line 103 "src/le_parser.y"
                            {
          Node *tmp = makeNode(StructField, NULL);
          addChild(tmp, makeNode(id, (yyvsp[-2].id)));
          addChild(tmp, (yyvsp[-1].node));
          (yyval.node) = tmp;
      }
#line 1291 "obj/le_parser.c"
    break;

  case 10: /* StructField: STRUCT IDENT Declarateurs ';'  */
#line 109 "src/le_parser.y"
                                    {
          Node *tmp = makeNode(StructField, NULL);
          addChild(tmp, makeNode(id, (yyvsp[-2].id))); // type struct déjà déclaré
          addChild(tmp, (yyvsp[-1].node));               // noms des champs
          (yyval.node) = tmp;
      }
#line 1302 "obj/le_parser.c"
    break;

  case 11: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 121 "src/le_parser.y"
                                   {
        Node *tmp = (yyvsp[-3].node) ? (yyvsp[-3].node) : makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        addChild(decl, makeNode(id, (yyvsp[-2].id)));
        addChild(decl, (yyvsp[-1].node));
        addChild(tmp, decl);
        (yyval.node) = tmp;
    }
#line 1315 "obj/le_parser.c"
    break;

  case 12: /* DeclVars: DeclVars STRUCT IDENT Declarateurs ';'  */
#line 129 "src/le_parser.y"
                                           {
        Node *tmp = (yyvsp[-4].node) ? (yyvsp[-4].node) : makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        Node *structType = makeNode(id, "struct");
        addChild(structType, makeNode(id, (yyvsp[-2].id))); // struct aircraft
        addChild(decl, structType);
        addChild(decl, (yyvsp[-1].node)); // a1, a2, etc.
        addChild(tmp, decl);
        (yyval.node) = tmp;
    }
#line 1330 "obj/le_parser.c"
    break;

  case 13: /* DeclVars: STRUCT IDENT Declarateurs ';'  */
#line 139 "src/le_parser.y"
                                  {  // <── ajout clé !
        Node *tmp = makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        Node *structType = makeNode(id, "struct");
        addChild(structType, makeNode(id, (yyvsp[-2].id)));
        addChild(decl, structType);
        addChild(decl, (yyvsp[-1].node));
        addChild(tmp, decl);
        (yyval.node) = tmp;
    }
#line 1345 "obj/le_parser.c"
    break;

  case 14: /* DeclVars: %empty  */
#line 149 "src/le_parser.y"
    { (yyval.node) = NULL; }
#line 1351 "obj/le_parser.c"
    break;

  case 15: /* Declarateurs: Declarateurs ',' IDENT  */
#line 155 "src/le_parser.y"
                           {
        Node *tmp = (yyvsp[-2].node) ? (yyvsp[-2].node) : makeNode(Declarateurs, NULL);
        addChild(tmp, makeNode(id, (yyvsp[0].id)));
        (yyval.node) = tmp;
    }
#line 1361 "obj/le_parser.c"
    break;

  case 16: /* Declarateurs: IDENT  */
#line 160 "src/le_parser.y"
          {
        Node *tmp = makeNode(Declarateurs, NULL);
        addChild(tmp, makeNode(id, (yyvsp[0].id)));
        (yyval.node) = tmp;
    }
#line 1371 "obj/le_parser.c"
    break;

  case 17: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 170 "src/le_parser.y"
                         {
        Node *tmp = (yyvsp[-1].node) ? (yyvsp[-1].node) : makeNode(DeclFoncts, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1381 "obj/le_parser.c"
    break;

  case 18: /* DeclFoncts: DeclFonct  */
#line 175 "src/le_parser.y"
              {
        Node *tmp = makeNode(DeclFoncts, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1391 "obj/le_parser.c"
    break;

  case 19: /* DeclFonct: EnTeteFonct Corps  */
#line 183 "src/le_parser.y"
                      {
        Node *tmp = makeNode(DeclFonct, NULL);
        addChild(tmp, (yyvsp[-1].node));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1402 "obj/le_parser.c"
    break;

  case 20: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 192 "src/le_parser.y"
                                  {
        Node *tmp = makeNode(EnTeteFonct, NULL);
        addChild(tmp, makeNode(id, (yyvsp[-4].id)));
        addChild(tmp, makeNode(id, (yyvsp[-3].id)));
        if ((yyvsp[-1].node)) addChild(tmp, (yyvsp[-1].node));
        (yyval.node) = tmp;
    }
#line 1414 "obj/le_parser.c"
    break;

  case 21: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 199 "src/le_parser.y"
                                  {
        Node *tmp = makeNode(EnTeteFonct, NULL);
        addChild(tmp, makeNode(id, (yyvsp[-4].id)));
        addChild(tmp, makeNode(id, (yyvsp[-3].id)));
        if ((yyvsp[-1].node)) addChild(tmp, (yyvsp[-1].node));
        (yyval.node) = tmp;
    }
#line 1426 "obj/le_parser.c"
    break;

  case 22: /* Parametres: VOID  */
#line 209 "src/le_parser.y"
         {
        Node *tmp = makeNode(Parametres, NULL);
        addChild(tmp, makeNode(id, (yyvsp[0].id)));
        (yyval.node) = tmp;
    }
#line 1436 "obj/le_parser.c"
    break;

  case 23: /* Parametres: ListTypVar  */
#line 214 "src/le_parser.y"
               {
        Node *tmp = makeNode(Parametres, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1446 "obj/le_parser.c"
    break;

  case 24: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 222 "src/le_parser.y"
                              {
        Node *tmp = (yyvsp[-3].node) ? (yyvsp[-3].node) : makeNode(ListTypVar, NULL);
        Node *param = makeNode(Parametres, NULL);
        addChild(param, makeNode(id, (yyvsp[-1].id)));
        addChild(param, makeNode(id, (yyvsp[0].id)));
        addChild(tmp, param);
        (yyval.node) = tmp;
    }
#line 1459 "obj/le_parser.c"
    break;

  case 25: /* ListTypVar: TYPE IDENT  */
#line 230 "src/le_parser.y"
               {
        Node *tmp = makeNode(ListTypVar, NULL);
        Node *param = makeNode(Parametres, NULL);
        addChild(param, makeNode(id, (yyvsp[-1].id)));
        addChild(param, makeNode(id, (yyvsp[0].id)));
        addChild(tmp, param);
        (yyval.node) = tmp;
    }
#line 1472 "obj/le_parser.c"
    break;

  case 26: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 243 "src/le_parser.y"
                                {
        Node *tmp = makeNode(Corps, NULL);
        if ((yyvsp[-2].node)) addChild(tmp, (yyvsp[-2].node));   
        if ((yyvsp[-1].node)) addChild(tmp, (yyvsp[-1].node));   
        (yyval.node) = tmp;
    }
#line 1483 "obj/le_parser.c"
    break;

  case 27: /* SuiteInstr: SuiteInstr Instr  */
#line 255 "src/le_parser.y"
                     {
        Node *tmp = (yyvsp[-1].node) ? (yyvsp[-1].node) : makeNode(SuiteInstr, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1493 "obj/le_parser.c"
    break;

  case 28: /* SuiteInstr: %empty  */
#line 260 "src/le_parser.y"
    { (yyval.node) = NULL; }
#line 1499 "obj/le_parser.c"
    break;

  case 29: /* Instr: IDENT '=' Exp ';'  */
#line 264 "src/le_parser.y"
                      {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, (yyvsp[-3].id)));
        addChild(tmp, makeNode(id, "="));
        addChild(tmp, (yyvsp[-1].node));
        (yyval.node) = tmp;
    }
#line 1511 "obj/le_parser.c"
    break;

  case 30: /* Instr: IF '(' Exp ')' Instr  */
#line 271 "src/le_parser.y"
                         {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, "if"));
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1523 "obj/le_parser.c"
    break;

  case 31: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 278 "src/le_parser.y"
                                    {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, "ifelse"));
        addChild(tmp, (yyvsp[-4].node));
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1536 "obj/le_parser.c"
    break;

  case 32: /* Instr: WHILE '(' Exp ')' Instr  */
#line 286 "src/le_parser.y"
                            {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, "while"));
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1548 "obj/le_parser.c"
    break;

  case 33: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 293 "src/le_parser.y"
                                {
        Node *tmp = makeNode(Instr, NULL);
        Node *callNode = makeNode(id, "call");
        addChild(callNode, makeNode(id, (yyvsp[-4].id)));
        if ((yyvsp[-2].node)) addChild(callNode, (yyvsp[-2].node));
        addChild(tmp, callNode);
        (yyval.node) = tmp;
    }
#line 1561 "obj/le_parser.c"
    break;

  case 34: /* Instr: RETURN Exp ';'  */
#line 301 "src/le_parser.y"
                   {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, "return"));
        addChild(tmp, (yyvsp[-1].node));
        (yyval.node) = tmp;
    }
#line 1572 "obj/le_parser.c"
    break;

  case 35: /* Instr: RETURN ';'  */
#line 307 "src/le_parser.y"
               {
        Node *tmp = makeNode(Instr, NULL);
        addChild(tmp, makeNode(id, "return"));
        (yyval.node) = tmp;
    }
#line 1582 "obj/le_parser.c"
    break;

  case 36: /* Instr: '{' SuiteInstr '}'  */
#line 312 "src/le_parser.y"
                       {
        if ((yyvsp[-1].node)) {
            Node *tmp = makeNode(Instr, NULL);
            addChild(tmp, (yyvsp[-1].node));
            (yyval.node) = tmp;
        } else {
            (yyval.node) = makeNode(Instr, "empty_block");
        }
    }
#line 1596 "obj/le_parser.c"
    break;

  case 37: /* Instr: ';'  */
#line 321 "src/le_parser.y"
        {
        (yyval.node) = makeNode(Instr, "empty_instr");
    }
#line 1604 "obj/le_parser.c"
    break;

  case 38: /* Exp: Exp OR TB  */
#line 329 "src/le_parser.y"
              {
        Node *tmp = makeNode(Exp, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, "||"));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1616 "obj/le_parser.c"
    break;

  case 39: /* Exp: TB  */
#line 336 "src/le_parser.y"
       { (yyval.node) = (yyvsp[0].node); }
#line 1622 "obj/le_parser.c"
    break;

  case 40: /* TB: TB AND FB  */
#line 340 "src/le_parser.y"
              {
        Node *tmp = makeNode(TB, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, "&&"));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1634 "obj/le_parser.c"
    break;

  case 41: /* TB: FB  */
#line 347 "src/le_parser.y"
       { (yyval.node) = (yyvsp[0].node); }
#line 1640 "obj/le_parser.c"
    break;

  case 42: /* FB: FB EQ M  */
#line 351 "src/le_parser.y"
            {
        Node *tmp = makeNode(FB, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, (yyvsp[-1].id)));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1652 "obj/le_parser.c"
    break;

  case 43: /* FB: M  */
#line 358 "src/le_parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1658 "obj/le_parser.c"
    break;

  case 44: /* M: M ORDER E  */
#line 362 "src/le_parser.y"
              {
        Node *tmp = makeNode(M, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, (yyvsp[-1].id)));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1670 "obj/le_parser.c"
    break;

  case 45: /* M: E  */
#line 369 "src/le_parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1676 "obj/le_parser.c"
    break;

  case 46: /* E: E ADDSUB T  */
#line 373 "src/le_parser.y"
               {
        Node *tmp = makeNode(E, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, (yyvsp[-1].id)));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1688 "obj/le_parser.c"
    break;

  case 47: /* E: T  */
#line 380 "src/le_parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1694 "obj/le_parser.c"
    break;

  case 48: /* T: T DIVSTAR F  */
#line 384 "src/le_parser.y"
                {
        Node *tmp = makeNode(T, NULL);
        addChild(tmp, (yyvsp[-2].node));
        addChild(tmp, makeNode(id, (yyvsp[-1].id)));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1706 "obj/le_parser.c"
    break;

  case 49: /* T: F  */
#line 391 "src/le_parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1712 "obj/le_parser.c"
    break;

  case 50: /* F: ADDSUB F  */
#line 395 "src/le_parser.y"
             {
        Node *tmp = makeNode(F, NULL);
        addChild(tmp, makeNode(id, (yyvsp[-1].id)));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1723 "obj/le_parser.c"
    break;

  case 51: /* F: '!' F  */
#line 401 "src/le_parser.y"
          {
        Node *tmp = makeNode(F, NULL);
        addChild(tmp, makeNode(id, "!"));
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1734 "obj/le_parser.c"
    break;

  case 52: /* F: '(' Exp ')'  */
#line 407 "src/le_parser.y"
                { (yyval.node) = (yyvsp[-1].node); }
#line 1740 "obj/le_parser.c"
    break;

  case 53: /* F: NUM  */
#line 408 "src/le_parser.y"
        {
        char buf[32]; snprintf(buf, sizeof(buf), "%d", (yyvsp[0].num));
        (yyval.node) = makeNode(num, buf);
    }
#line 1749 "obj/le_parser.c"
    break;

  case 54: /* F: CHARACTER  */
#line 412 "src/le_parser.y"
              {
        char buf[2]; buf[0] = (yyvsp[0].character); buf[1] = '\0';
        (yyval.node) = makeNode(id, buf);
    }
#line 1758 "obj/le_parser.c"
    break;

  case 55: /* F: IDENT  */
#line 416 "src/le_parser.y"
          { (yyval.node) = makeNode(id, (yyvsp[0].id)); }
#line 1764 "obj/le_parser.c"
    break;

  case 56: /* F: IDENT '(' Arguments ')'  */
#line 417 "src/le_parser.y"
                            {
        Node *tmp = makeNode(F, NULL);
        Node *callNode = makeNode(id, "call");
        addChild(callNode, makeNode(id, (yyvsp[-3].id)));
        if ((yyvsp[-1].node)) addChild(callNode, (yyvsp[-1].node));
        addChild(tmp, callNode);
        (yyval.node) = tmp;
    }
#line 1777 "obj/le_parser.c"
    break;

  case 57: /* Arguments: ListExp  */
#line 430 "src/le_parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1783 "obj/le_parser.c"
    break;

  case 58: /* Arguments: %empty  */
#line 431 "src/le_parser.y"
    { (yyval.node) = NULL; }
#line 1789 "obj/le_parser.c"
    break;

  case 59: /* ListExp: ListExp ',' Exp  */
#line 435 "src/le_parser.y"
                    {
        Node *tmp = (yyvsp[-2].node) ? (yyvsp[-2].node) : makeNode(ListExp, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1799 "obj/le_parser.c"
    break;

  case 60: /* ListExp: Exp  */
#line 440 "src/le_parser.y"
        {
        Node *tmp = makeNode(ListExp, NULL);
        addChild(tmp, (yyvsp[0].node));
        (yyval.node) = tmp;
    }
#line 1809 "obj/le_parser.c"
    break;


#line 1813 "obj/le_parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 447 "src/le_parser.y"


int yyparse();

int main(int argc, char *argv[]) {
    int opt, show_tree = 0;

    struct option long_options[] = {
        {"tree", no_argument, NULL, 't'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "th", long_options, NULL)) != -1) {
        switch (opt) {
            case 't': show_tree = 1; break;
            case 'h': print_help(); return 0;
            default:
                fprintf(stderr, "Option invalide : -%c\n", opt);
                print_help(); return 2;
        }
    }

    printf("Début de l'analyse syntaxique...\n");
    if (yyparse() == 0) {
        printf("Analyse syntaxique réussie.\n");
        if (show_tree && root) printTree(root);
        return 0;
    } else {
        printf("Erreur d'analyse syntaxique.\n");
        return 1;
    }
}
