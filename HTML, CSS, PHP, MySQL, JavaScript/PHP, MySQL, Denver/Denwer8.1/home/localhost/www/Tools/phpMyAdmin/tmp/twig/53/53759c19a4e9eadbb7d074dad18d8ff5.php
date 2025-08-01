<?php

use Twig\Environment;
use Twig\Error\LoaderError;
use Twig\Error\RuntimeError;
use Twig\Extension\SandboxExtension;
use Twig\Markup;
use Twig\Sandbox\SecurityError;
use Twig\Sandbox\SecurityNotAllowedTagError;
use Twig\Sandbox\SecurityNotAllowedFilterError;
use Twig\Sandbox\SecurityNotAllowedFunctionError;
use Twig\Source;
use Twig\Template;

/* javascript/variables.twig */
class __TwigTemplate_1600949714729ff1159f26fe9d282a36 extends Template
{
    private $source;
    private $macros = [];

    public function __construct(Environment $env)
    {
        parent::__construct($env);

        $this->source = $this->getSourceContext();

        $this->parent = false;

        $this->blocks = [
        ];
    }

    protected function doDisplay(array $context, array $blocks = [])
    {
        $macros = $this->macros;
        // line 2
        echo "var firstDayOfCalendar = '";
        echo twig_escape_filter($this->env, ($context["first_day_of_calendar"] ?? null), "js", null, true);
        echo "';
var themeImagePath = '";
        // line 3
        echo twig_escape_filter($this->env, $this->extensions['PhpMyAdmin\Twig\AssetExtension']->getImagePath(), "js", null, true);
        echo "';
var mysqlDocTemplate = '";
        // line 4
        echo twig_escape_filter($this->env, PhpMyAdmin\Util::getMySQLDocuURL("%s"), "js", null, true);
        echo "';
var maxInputVars = ";
        // line 5
        echo twig_escape_filter($this->env, ($context["max_input_vars"] ?? null), "js", null, true);
        echo ";

";
        // line 7
        ob_start(function () { return ''; });
// l10n: Month-year order for calendar, use either "calendar-month-year" or "calendar-year-month".
echo _gettext("calendar-month-year");
        $context["show_month_after_year"] = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        // line 10
        ob_start(function () { return ''; });
// l10n: Year suffix for calendar, "none" is empty.
echo _gettext("none");
        $context["year_suffix"] = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        // line 14
        echo "if (\$.datepicker) {
  \$.datepicker.regional[''].closeText = '";
        // line 15
        ob_start(function () { return ''; });
// l10n: Display text for calendar close link
echo _gettext("Done");
        $___internal_parse_1_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_1_, "js");
        echo "';
  \$.datepicker.regional[''].prevText = '";
        // line 16
        ob_start(function () { return ''; });
// l10n: Previous month. Display text for previous month link in calendar
echo _gettext("Prev");
        $___internal_parse_2_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_2_, "js");
        echo "';
  \$.datepicker.regional[''].nextText = '";
        // line 17
        ob_start(function () { return ''; });
// l10n: Next month. Display text for next month link in calendar
echo _gettext("Next");
        $___internal_parse_3_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_3_, "js");
        echo "';
  \$.datepicker.regional[''].currentText = '";
        // line 18
        ob_start(function () { return ''; });
// l10n: Display text for current month link in calendar
echo _gettext("Today");
        $___internal_parse_4_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_4_, "js");
        echo "';
  \$.datepicker.regional[''].monthNames = [
    '";
        // line 20
        echo twig_escape_filter($this->env, _gettext("January"), "js", null, true);
        echo "',
    '";
        // line 21
        echo twig_escape_filter($this->env, _gettext("February"), "js", null, true);
        echo "',
    '";
        // line 22
        echo twig_escape_filter($this->env, _gettext("March"), "js", null, true);
        echo "',
    '";
        // line 23
        echo twig_escape_filter($this->env, _gettext("April"), "js", null, true);
        echo "',
    '";
        // line 24
        echo twig_escape_filter($this->env, _gettext("May"), "js", null, true);
        echo "',
    '";
        // line 25
        echo twig_escape_filter($this->env, _gettext("June"), "js", null, true);
        echo "',
    '";
        // line 26
        echo twig_escape_filter($this->env, _gettext("July"), "js", null, true);
        echo "',
    '";
        // line 27
        echo twig_escape_filter($this->env, _gettext("August"), "js", null, true);
        echo "',
    '";
        // line 28
        echo twig_escape_filter($this->env, _gettext("September"), "js", null, true);
        echo "',
    '";
        // line 29
        echo twig_escape_filter($this->env, _gettext("October"), "js", null, true);
        echo "',
    '";
        // line 30
        echo twig_escape_filter($this->env, _gettext("November"), "js", null, true);
        echo "',
    '";
        // line 31
        echo twig_escape_filter($this->env, _gettext("December"), "js", null, true);
        echo "',
  ];
  \$.datepicker.regional[''].monthNamesShort = [
    '";
        // line 34
        ob_start(function () { return ''; });
// l10n: Short month name for January
echo _gettext("Jan");
        $___internal_parse_5_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_5_, "js");
        echo "',
    '";
        // line 35
        ob_start(function () { return ''; });
// l10n: Short month name for February
echo _gettext("Feb");
        $___internal_parse_6_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_6_, "js");
        echo "',
    '";
        // line 36
        ob_start(function () { return ''; });
// l10n: Short month name for March
echo _gettext("Mar");
        $___internal_parse_7_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_7_, "js");
        echo "',
    '";
        // line 37
        ob_start(function () { return ''; });
// l10n: Short month name for April
echo _gettext("Apr");
        $___internal_parse_8_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_8_, "js");
        echo "',
    '";
        // line 38
        ob_start(function () { return ''; });
// l10n: Short month name for May
echo _gettext("May");
        $___internal_parse_9_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_9_, "js");
        echo "',
    '";
        // line 39
        ob_start(function () { return ''; });
// l10n: Short month name for June
echo _gettext("Jun");
        $___internal_parse_10_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_10_, "js");
        echo "',
    '";
        // line 40
        ob_start(function () { return ''; });
// l10n: Short month name for July
echo _gettext("Jul");
        $___internal_parse_11_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_11_, "js");
        echo "',
    '";
        // line 41
        ob_start(function () { return ''; });
// l10n: Short month name for August
echo _gettext("Aug");
        $___internal_parse_12_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_12_, "js");
        echo "',
    '";
        // line 42
        ob_start(function () { return ''; });
// l10n: Short month name for September
echo _gettext("Sep");
        $___internal_parse_13_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_13_, "js");
        echo "',
    '";
        // line 43
        ob_start(function () { return ''; });
// l10n: Short month name for October
echo _gettext("Oct");
        $___internal_parse_14_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_14_, "js");
        echo "',
    '";
        // line 44
        ob_start(function () { return ''; });
// l10n: Short month name for November
echo _gettext("Nov");
        $___internal_parse_15_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_15_, "js");
        echo "',
    '";
        // line 45
        ob_start(function () { return ''; });
// l10n: Short month name for December
echo _gettext("Dec");
        $___internal_parse_16_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_16_, "js");
        echo "',
  ];
  \$.datepicker.regional[''].dayNames = [
    '";
        // line 48
        echo twig_escape_filter($this->env, _gettext("Sunday"), "js", null, true);
        echo "',
    '";
        // line 49
        echo twig_escape_filter($this->env, _gettext("Monday"), "js", null, true);
        echo "',
    '";
        // line 50
        echo twig_escape_filter($this->env, _gettext("Tuesday"), "js", null, true);
        echo "',
    '";
        // line 51
        echo twig_escape_filter($this->env, _gettext("Wednesday"), "js", null, true);
        echo "',
    '";
        // line 52
        echo twig_escape_filter($this->env, _gettext("Thursday"), "js", null, true);
        echo "',
    '";
        // line 53
        echo twig_escape_filter($this->env, _gettext("Friday"), "js", null, true);
        echo "',
    '";
        // line 54
        echo twig_escape_filter($this->env, _gettext("Saturday"), "js", null, true);
        echo "',
  ];
  \$.datepicker.regional[''].dayNamesShort = [
    '";
        // line 57
        ob_start(function () { return ''; });
// l10n: Short week day name for Sunday
echo _gettext("Sun");
        $___internal_parse_17_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_17_, "js");
        echo "',
    '";
        // line 58
        ob_start(function () { return ''; });
// l10n: Short week day name for Monday
echo _gettext("Mon");
        $___internal_parse_18_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_18_, "js");
        echo "',
    '";
        // line 59
        ob_start(function () { return ''; });
// l10n: Short week day name for Tuesday
echo _gettext("Tue");
        $___internal_parse_19_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_19_, "js");
        echo "',
    '";
        // line 60
        ob_start(function () { return ''; });
// l10n: Short week day name for Wednesday
echo _gettext("Wed");
        $___internal_parse_20_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_20_, "js");
        echo "',
    '";
        // line 61
        ob_start(function () { return ''; });
// l10n: Short week day name for Thursday
echo _gettext("Thu");
        $___internal_parse_21_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_21_, "js");
        echo "',
    '";
        // line 62
        ob_start(function () { return ''; });
// l10n: Short week day name for Friday
echo _gettext("Fri");
        $___internal_parse_22_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_22_, "js");
        echo "',
    '";
        // line 63
        ob_start(function () { return ''; });
// l10n: Short week day name for Saturday
echo _gettext("Sat");
        $___internal_parse_23_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_23_, "js");
        echo "',
  ];
  \$.datepicker.regional[''].dayNamesMin = [
    '";
        // line 66
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Sunday
echo _gettext("Su");
        $___internal_parse_24_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_24_, "js");
        echo "',
    '";
        // line 67
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Monday
echo _gettext("Mo");
        $___internal_parse_25_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_25_, "js");
        echo "',
    '";
        // line 68
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Tuesday
echo _gettext("Tu");
        $___internal_parse_26_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_26_, "js");
        echo "',
    '";
        // line 69
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Wednesday
echo _gettext("We");
        $___internal_parse_27_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_27_, "js");
        echo "',
    '";
        // line 70
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Thursday
echo _gettext("Th");
        $___internal_parse_28_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_28_, "js");
        echo "',
    '";
        // line 71
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Friday
echo _gettext("Fr");
        $___internal_parse_29_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_29_, "js");
        echo "',
    '";
        // line 72
        ob_start(function () { return ''; });
// l10n: Minimal week day name for Saturday
echo _gettext("Sa");
        $___internal_parse_30_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_30_, "js");
        echo "',
  ];
  \$.datepicker.regional[''].weekHeader = '";
        // line 74
        ob_start(function () { return ''; });
// l10n: Column header for week of the year in calendar
echo _gettext("Wk");
        $___internal_parse_31_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_31_, "js");
        echo "';
  \$.datepicker.regional[''].showMonthAfterYear = ";
        // line 75
        echo (((($context["show_month_after_year"] ?? null) == "calendar-year-month")) ? ("true") : ("false"));
        echo ";
  \$.datepicker.regional[''].yearSuffix = '";
        // line 76
        echo (((($context["year_suffix"] ?? null) != "none")) ? (twig_escape_filter($this->env, ($context["year_suffix"] ?? null), "js")) : (""));
        echo "';
  \$.extend(\$.datepicker._defaults, \$.datepicker.regional['']);
}

if (\$.timepicker) {
  \$.timepicker.regional[''].timeText = '";
        // line 81
        echo twig_escape_filter($this->env, _gettext("Time"), "js", null, true);
        echo "';
  \$.timepicker.regional[''].hourText = '";
        // line 82
        echo twig_escape_filter($this->env, _gettext("Hour"), "js", null, true);
        echo "';
  \$.timepicker.regional[''].minuteText = '";
        // line 83
        echo twig_escape_filter($this->env, _gettext("Minute"), "js", null, true);
        echo "';
  \$.timepicker.regional[''].secondText = '";
        // line 84
        echo twig_escape_filter($this->env, _gettext("Second"), "js", null, true);
        echo "';
  \$.extend(\$.timepicker._defaults, \$.timepicker.regional['']);
}

function extendingValidatorMessages () {
  \$.extend(\$.validator.messages, {
    required: '";
        // line 90
        echo twig_escape_filter($this->env, _gettext("This field is required"), "js", null, true);
        echo "',
    remote: '";
        // line 91
        echo twig_escape_filter($this->env, _gettext("Please fix this field"), "js", null, true);
        echo "',
    email: '";
        // line 92
        echo twig_escape_filter($this->env, _gettext("Please enter a valid email address"), "js", null, true);
        echo "',
    url: '";
        // line 93
        echo twig_escape_filter($this->env, _gettext("Please enter a valid URL"), "js", null, true);
        echo "',
    date: '";
        // line 94
        echo twig_escape_filter($this->env, _gettext("Please enter a valid date"), "js", null, true);
        echo "',
    dateISO: '";
        // line 95
        echo twig_escape_filter($this->env, _gettext("Please enter a valid date ( ISO )"), "js", null, true);
        echo "',
    number: '";
        // line 96
        echo twig_escape_filter($this->env, _gettext("Please enter a valid number"), "js", null, true);
        echo "',
    creditcard: '";
        // line 97
        echo twig_escape_filter($this->env, _gettext("Please enter a valid credit card number"), "js", null, true);
        echo "',
    digits: '";
        // line 98
        echo twig_escape_filter($this->env, _gettext("Please enter only digits"), "js", null, true);
        echo "',
    equalTo: '";
        // line 99
        echo twig_escape_filter($this->env, _gettext("Please enter the same value again"), "js", null, true);
        echo "',
    maxlength: \$.validator.format('";
        // line 100
        echo twig_escape_filter($this->env, _gettext("Please enter no more than {0} characters"), "js", null, true);
        echo "'),
    minlength: \$.validator.format('";
        // line 101
        echo twig_escape_filter($this->env, _gettext("Please enter at least {0} characters"), "js", null, true);
        echo "'),
    rangelength: \$.validator.format('";
        // line 102
        echo twig_escape_filter($this->env, _gettext("Please enter a value between {0} and {1} characters long"), "js", null, true);
        echo "'),
    range: \$.validator.format('";
        // line 103
        echo twig_escape_filter($this->env, _gettext("Please enter a value between {0} and {1}"), "js", null, true);
        echo "'),
    max: \$.validator.format('";
        // line 104
        echo twig_escape_filter($this->env, _gettext("Please enter a value less than or equal to {0}"), "js", null, true);
        echo "'),
    min: \$.validator.format('";
        // line 105
        echo twig_escape_filter($this->env, _gettext("Please enter a value greater than or equal to {0}"), "js", null, true);
        echo "'),
    validationFunctionForDateTime: \$.validator.format('";
        // line 106
        echo twig_escape_filter($this->env, _gettext("Please enter a valid date or time"), "js", null, true);
        echo "'),
    validationFunctionForHex: \$.validator.format('";
        // line 107
        echo twig_escape_filter($this->env, _gettext("Please enter a valid HEX input"), "js", null, true);
        echo "'),
    validationFunctionForMd5: \$.validator.format('";
        // line 108
        ob_start(function () { return ''; });
// l10n: To validate the usage of a MD5 function on the column
echo _gettext("This column can not contain a 32 chars value");
        $___internal_parse_32_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_32_, "js");
        echo "'),
    validationFunctionForAesDesEncrypt: \$.validator.format('";
        // line 109
        ob_start(function () { return ''; });
// l10n: To validate the usage of a AES_ENCRYPT/DES_ENCRYPT function on the column
echo _gettext("These functions are meant to return a binary result; to avoid inconsistent results you should store it in a BINARY, VARBINARY, or BLOB column.");
        $___internal_parse_33_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
        echo twig_escape_filter($this->env, $___internal_parse_33_, "js");
        echo "')
  });
}
";
    }

    public function getTemplateName()
    {
        return "javascript/variables.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  515 => 109,  507 => 108,  503 => 107,  499 => 106,  495 => 105,  491 => 104,  487 => 103,  483 => 102,  479 => 101,  475 => 100,  471 => 99,  467 => 98,  463 => 97,  459 => 96,  455 => 95,  451 => 94,  447 => 93,  443 => 92,  439 => 91,  435 => 90,  426 => 84,  422 => 83,  418 => 82,  414 => 81,  406 => 76,  402 => 75,  394 => 74,  385 => 72,  377 => 71,  369 => 70,  361 => 69,  353 => 68,  345 => 67,  337 => 66,  327 => 63,  319 => 62,  311 => 61,  303 => 60,  295 => 59,  287 => 58,  279 => 57,  273 => 54,  269 => 53,  265 => 52,  261 => 51,  257 => 50,  253 => 49,  249 => 48,  239 => 45,  231 => 44,  223 => 43,  215 => 42,  207 => 41,  199 => 40,  191 => 39,  183 => 38,  175 => 37,  167 => 36,  159 => 35,  151 => 34,  145 => 31,  141 => 30,  137 => 29,  133 => 28,  129 => 27,  125 => 26,  121 => 25,  117 => 24,  113 => 23,  109 => 22,  105 => 21,  101 => 20,  92 => 18,  84 => 17,  76 => 16,  68 => 15,  65 => 14,  60 => 10,  55 => 7,  50 => 5,  46 => 4,  42 => 3,  37 => 2,);
    }

    public function getSourceContext()
    {
        return new Source("", "javascript/variables.twig", "Z:\\home\\localhost\\www\\Tools\\phpMyAdmin\\templates\\javascript\\variables.twig");
    }
}
