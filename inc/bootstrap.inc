<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

// An interface to bootstrap navbars and grids.
//Edited by Thomas Johnson and Gerald Joshua

$fixed_navbar = false;

if (defined('REMOTE_JOB_SUBMISSION') && REMOTE_JOB_SUBMISSION) {
    require_once("../inc/submit_db.inc");
}

////////////// NAVBAR ////////////////

// call this to start the navbar.
// $brand: the text or image to show at left of navbar
// If text, put it in <a class="navbar-brand" ...
//
function navbar_start($brand, $fixed, $inverse) {
    global $fixed_navbar;
    $class = "navbar";
    if ($inverse) {
        $class .= " navbar-inverse";
    } else {
        $class .= " navbar-default";
    }
    if ($fixed) {
        $class .= " navbar-fixed-top";
        $fixed_navbar = true;
    }
    echo "<nav class=\"$class\">\n";
    echo '
  <div class="container-fluid">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#myNavbar">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      '.$brand.'
    </div>
    <div class="collapse navbar-collapse" id="myNavbar">
      <ul class="nav navbar-nav">
    ';
}

// call this to end it
//
function navbar_end() {
    echo '
      </ul>
    </div>
  </div>
</nav>
<!-- Added by Gerald Joshua, so there is enough space
between navbar and the content -->
<br /><br />
<!-- End of Gerald Joshuas edit -->
    ';
}

// put the login/logout stuff at the right side of navbar
//
//Edit by Thomas Johnson: Drop down menus for Sign Up and Login webpages
function navbar_right($user) {
    global $is_login_page;
    echo '
      </ul>
      <ul class="nav navbar-nav navbar-right">
    ';
    if (!$is_login_page) {
        if ($user) {
            echo sprintf('
                <li><a href=%s%s>%s</a></li>
                ', url_base(), USER_HOME, $user->name
            );
            $url_tokens = url_tokens($user->authenticator);
            echo sprintf('<li><a href="%slogout.php?%s">Log out</a></li>',
                url_base(), $url_tokens
            );
        } else {
            echo sprintf('
                <li class="dropdown">
                <a class="dropdown-toggle" data-toggle="dropdown" href="#">Sign Up
                <span class="caret"></span></a>
                <ul class="dropdown-menu">
                <li><a href="%screate_account_form.php">Sign Up as a Volunteer</a></li>
                <li><a href="%screate_researcher_account_form.php" style="pointer-events:none; color:gray;">Sign Up as a Researcher</a></li>
                </ul></li>
                <li class="dropdown">
                <a class="dropdown-toggle" data-toggle="dropdown" href="#">Log In
                <span class="caret"></span></a>
                <ul class="dropdown-menu">
                <li><a href="%slogin_form.php">Log In as a Volunteer</a></li>
                <li><a href="%slogin_as_a_researcher_form.php">Log In as a Researcher</a></li>
                </ul></li>
                ', url_base(), url_base(),url_base(),url_base()
            );
        }
    }
}
/* https://getbootstrap.com/docs/4.0/components/navbar/
<nav class="navbar navbar-expand-lg navbar-light bg-light">
  <a class="navbar-brand" href="#">Navbar</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>

  <div class="collapse navbar-collapse" id="navbarSupportedContent">
    <ul class="navbar-nav mr-auto">
      <li class="nav-item active">
        <a class="nav-link" href="#">Home <span class="sr-only">(current)</span></a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="#">Link</a>
      </li>
      <li class="nav-item dropdown">
        <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
          Dropdown
        </a>
        <div class="dropdown-menu" aria-labelledby="navbarDropdown">
          <a class="dropdown-item" href="#">Action</a>
          <a class="dropdown-item" href="#">Another action</a>
          <div class="dropdown-divider"></div>
          <a class="dropdown-item" href="#">Something else here</a>
        </div>
      </li>
      <li class="nav-item">
        <a class="nav-link disabled" href="#">Disabled</a>
      </li>
    </ul>
    <form class="form-inline my-2 my-lg-0">
      <input class="form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search">
      <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
    </form>
  </div>
</nav>

*/
/*
navbar_menu(tra("Sign Up"), array(
array(tra("As Researcher"), $url_prefix."create_researcher_account_form.php"),
array(tra("As Volunteer"), $url_prefix."create_account_form.php")
));

navbar_menu(tra("Log In"), array(
array(tra("As Researcher"), $url_prefix."login_as_a_researcher_form.php"),
array(tra("As Volunteer"), $url_prefix."login_form.php")
));

*/
// add a dropdown menu
//
function navbar_menu($name, $items) {
    echo '
      <li class="dropdown">
        <a class="dropdown-toggle" data-toggle="dropdown" href="#">'.$name.'
        <span class="caret"></span></a>
        <ul class="dropdown-menu">
    ';
    foreach ($items as $item) {
        if (is_array($item)) {
            echo '<li><a href="'.$item[1].'">'.$item[0].'</a></li>
            ';
        } else {
            echo '<li class="dropdown-header">'.$item.'</li>
            ';
        }
    }
    echo '
        </ul>
      </li>
    ';
}

// add a single item (not menu)
//
function navbar_item($name, $url) {
    echo '<li><a href="'.$url.'">'.$name.'</a></li>
    ';
}

// A generic navbar.
// Call this from project_banner().
// If you want to customized it, copy it to your project.inc
// and give it a new name
//
function sample_navbar(
    $url_prefix,
        // prefix for links; needed for pages not in top dir
    $user,
        // logged-in user, if any
    $fixed=false,
        // if true, navbar is fixed at top of page.
        // NOTE: if you do this, you must set a global var $fixed_navbar
        // to true at compile time
        // (it needs to be set when page_head() is called).
    $inverse=false
        // white on black?
) {
    global $master_url;

    //$brand = "<a class=\"navbar-brand\" href=$master_url>".PROJECT."</a>";
    navbar_start(null, $fixed, $inverse);//First argument was $brand

    navbar_item("About", "http://129.114.16.64/boincserver/about.php");

    $x = array();
    if ($user) {
        $x[] = array(tra("Account"), $url_prefix.USER_HOME);
        $x[] = array(tra("Join"), $url_prefix."join.php");
        $x[] = array(tra("Preferences"), $url_prefix."prefs.php?subset=project");
    }
    //Commented out Project Drop Dow as it was determined that its information could be merged into the project panel.
    /*
    $x[] = array(tra("About %1", PROJECT), $url_prefix."about.php");
    $x[] = array(tra("Help"), $url_prefix."help.php");
    navbar_menu(tra("Project"), $x);
    */
    if (NO_COMPUTING) {
        // this is for projects that don't do computing, e.g. BOSSA-based
        //
        if (defined('BOSSA')) {
            navbar_menu(tra("Participate"), array(
                array(tra("Do work"), $url_prefix."bossa_apps.php"),
            ));
        }
    } else {
        $x = array(
            array(tra("Preferences"), $url_prefix."prefs.php?subset=global"),
            array(tra("Server status"), $url_prefix."server_status.php"),
            array(tra("Statistics"), $url_prefix."stats.php"),
            array(tra("Applications"), $url_prefix."apps.php"),
        );
        if (defined('REMOTE_JOB_SUBMISSION') && REMOTE_JOB_SUBMISSION) {
            if ($user && BoincUserSubmit::lookup_userid($user->id)) {
                $x[] = array("Job submission", $url_prefix."submit.php");
            }
        }
        $x = array_merge($x,
            array(
                'Leader boards:',
                array(tra("Participants"), $url_prefix."top_users.php"),
                array(tra("Computers"), $url_prefix."top_hosts.php"),
                array(tra("Teams"), $url_prefix."top_teams.php"),
                array(tra("GPU models"), $url_prefix."gpu_list.php"),
                array(tra("CPU models"), $url_prefix."cpu_list.php"),
            )
        );
        navbar_menu(tra("Computing"), $x);
    }

    navbar_menu(tra("Community"), array(
        array(tra("Message boards"), $url_prefix."forum_index.php"),
        //array(tra("Questions and Answers"), $url_prefix."forum_help_desk.php"),
        array(tra("Teams"), $url_prefix."team.php", tra("create or join a team")),
        array(tra("Profiles"), $url_prefix."profile_menu.php"),
        array(tra("Preferences"), $url_prefix."edit_forum_preferences_form.php"),
        array(tra("User search"), $url_prefix."user_search.php"),
        array(tra("User of the day"), $url_prefix."uotd.php"),
        array(tra("Certificate"), $url_prefix."cert1.php", "", "_blank"),
    ));
    navbar_menu(tra("Site"), array(
        array(tra("Site search"), $url_prefix."site_search.php"),
        array(tra("Languages"), $url_prefix."language_select.php")
    ));

    // add your own menu here if you want
    //Added by Gerald Joshua
    //News menu on the navbar that is accessible to the public
    navbar_item("News", "http://129.114.16.64/boincserver/news.php");
    /*Added by Thomas Johnson for reference and as temporary placeholder
    navbar_menu(tra("Sign Up"), array(
    array(tra("As Researcher"), $url_prefix."create_researcher_account_form.php"),
    array(tra("As Volunteer"), $url_prefix."create_account_form.php")
    ));

    navbar_menu(tra("Log In"), array(
    array(tra("As Researcher"), $url_prefix."login_as_a_researcher_form.php"),
    array(tra("As Volunteer"), $url_prefix."login_form.php")
    ));
    */
    //Job Submission and Job History menus on the navbar
    //will only be available to researchers
    if($user){
    	navbar_item("Job Submission", "http://129.114.16.64/boincserver/job_submission.php");
        navbar_item("Job History", "http://129.114.16.64/boincserver/job_history.php");
    }
    //End of Gerald Joshua's edit
    navbar_right($user);
    navbar_end();
}

// output a panel.
// $content_func is a function that generates the panel contents
//
function panel($title, $content_func, $class="panel-primary") {
    echo sprintf('<div class="panel %s">
        ', $class
    );
    if ($title) {
        echo '
            <div class="panel-heading">
                <h1 class="panel-title">'.$title.'</h1>
            </div>
        ';
    }
    echo '
        <div class="panel-body">
    ';
    $content_func();
    echo '
        </div>
        </div>
    ';
}

// grid layout with a full-width row followed by two equal columns
// $top_func, $left_func, and $right_func
// are functions that generate the top, left, and right content
// $left_width is the width of left column in 1/12 units.
//
function grid($top_func, $left_func, $right_func, $left_width=6) {
    echo '
        <div class="container-fluid">
    ';
    if ($top_func) {
        echo '
            <div class="row">
            <div class="col-sm-12">
        ';
        $top_func();
        echo '
            </div>
            </div>
        ';
    }
    $right_width = 12-$left_width;
    echo '
        <div class="row">
        <div class="col-sm-'.$left_width.'">
    ';
    $left_func();
    echo '
        </div>
        <div class="col-sm-'.$right_width.'">
    ';
    $right_func();
    echo '
        </div>
        </div>
        </div>
    ';
}

function form_start($action, $method='get') {
    echo sprintf(
        '<div class="container">
        <form class="form-horizontal" method="%s" action="%s">'
        ,
        $method, $action
    );
}

function form_input_hidden($name, $value) {
    echo '<input type="hidden" name="'.$name.'" value="'.$value.'">
    ';
}

function form_end() {
    echo '</form>
        </div>
    ';
}

define('FORM_LEFT_CLASS', 'col-sm-4');
define('FORM_LEFT_OFFSET', 'col-sm-offset-4');
define('FORM_RIGHT_CLASS', 'col-sm-8');

function form_input_text($label, $name, $value='', $type='text', $attrs='', $extra='') {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s">%s</label>
            <div class="%s">
                <input %s type="%s" class="form-control" name="%s" value="%s">%s
            </div>
        </div>
        ',
        FORM_LEFT_CLASS, $label, FORM_RIGHT_CLASS,
        $attrs, $type, $name, $value, $extra
    );
}

// display name/value with same formatting as form
//
function form_attr($name, $value) {
    echo sprintf('
        <div class="form-group">
            <div class="%s text-right">%s</div>
            <div class="%s">%s</div>
        </div>
        ',
        FORM_LEFT_CLASS, $name, FORM_RIGHT_CLASS, $value
    );
}

function form_input_textarea($label, $name, $value='') {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s" for="%s">%s</label>
            <div class="%s">
                <textarea rows="6" class="form-control" id="%s" name="%s">%s</textarea>
            </div>
        </div>
        ',
        FORM_LEFT_CLASS, $name, $label, FORM_RIGHT_CLASS, $name, $name, $value
    );
}

// $items is either a string of <option> elements, or an array
//
function form_select($label, $name, $items) {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s" for="%s">%s</label>
            <div class="%s">
                <select class="form-control" id="%s" name="%s">
        ',
        FORM_LEFT_CLASS, $name, $label, FORM_RIGHT_CLASS, $name, $name
    );
    if (is_array($items)) {
        foreach ($items as $i) {
            echo '<option value="'.$i[0].'">'.$i[1].'</option>
            ';
        }
    } else {
        echo $items;
    }
    echo "</select></div></div>\n";
}

// same, for multiple select.
// flags, if non-null, says which ones are selected
//
function form_select_multiple($label, $name, $items, $flags) {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s" for="%s">%s</label>
            <div class="%s">
                <select multiple class="form-control" id="%s" name="%s[]">
        ',
        FORM_LEFT_CLASS, $name, $label, FORM_RIGHT_CLASS, $name, $name
    );
    $n = 0;
    foreach ($items as $i) {
        $s = ($flags && $flags[$n])?'selected':'';
        echo '<option '.$s.' value="'.$i[0].'">'.$i[1].'</option>
        ';
        $n++;
    }
    echo "</select></div></div>\n";
}

// $items is list of (name, label, checked)
//
function form_checkboxes($label, $items) {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s">%s</label>
            <div class="%s">
        ',
        FORM_LEFT_CLASS, $label, FORM_RIGHT_CLASS
    );
    $first = true;
    foreach ($items as $i) {
        if ($first) {
            $first = false;
        } else {
            echo "<br>\n";
        }
        echo sprintf('<input type="checkbox" name="%s" %s> %s
            ',
            $i[0], $i[2]?"checked":"", $i[1]
        );
    }
    echo '</div>
        </div>
    ';
}

// $items is list of (value, label)
//
function form_radio_buttons($label, $name, $items, $selected) {
    echo sprintf('
        <div class="form-group">
            <label class="control-label %s">%s</label>
            <div class="%s">
        ',
        FORM_LEFT_CLASS, $label, FORM_RIGHT_CLASS
    );
    foreach ($items as $i) {
        $checked = ($selected == $i[0])?"checked":"";
        echo sprintf('<input type="radio" name="%s" value="%s" %s> %s <br>
            ',
            $name, $i[0], $checked, $i[1]
        );
    }
    echo '</div>
        </div>
    ';
}

function form_general($label, $item) {
    echo '
        <div class="form-group">
    ';
    if (strlen($label)) {
        echo sprintf(
'           <label class="control-label %s">%s</label>
            <div class="%s">%s</div>
        ',
            FORM_LEFT_CLASS, $label, FORM_RIGHT_CLASS, $item
        );
    } else {
        echo sprintf(
'           <div class="%s %s">%s</div>
        ',
            FORM_LEFT_OFFSET, FORM_RIGHT_CLASS, $item
        );
    }
    echo '</div>
';
}

function form_submit($text) {
    form_general(
        "",
        sprintf('<button type="submit" class="btn btn-success">%s</button>',
            $text
        )
    );
}

function form_checkbox($label, $name, $checked=false) {
    echo sprintf('
        <div class="form-group">
            <input type="checkbox" name="%s" %s> &nbsp; <span class="lead">%s</span>
        </div>
        ', $name, $checked?"checked":"", $label
    );
}


