<?php
function isLoggedIn() {
    $inSession = session_id();
    if (!empty($inSession)) {
        if (isset($_SESSION['loggedin'])) {
            return $_SESSION['loggedin'];
        }
    }
    return false;
}

function ensureLoggedIn() {
    if (!isLoggedIn()) {
        $_SESSION['redirect'] = $_SERVER['REQUEST_URI'];
        redirectRelative('login');
        exit();
    }
}

function markdown($str) {
    $str = htmlspecialchars(ltrim($str),ENT_QUOTES);
    $str = preg_replace('/\*\*(.+)\*\*/u', '<strong>$1</strong>', $str);
    $str = preg_replace('/\*([^\*]+)\*/u', '<em>$1</em>', $str);
    $str = preg_replace('/#### ([^\n]*)\n/', "<h4>$1</h4>\n", $str);
    $str = preg_replace('/### ([^\n]*)\n/', "<h3>$1</h3>\n", $str);
    $str = preg_replace('/## ([^\n]*)\n/', "<h2>$1</h2>\n", $str);
    $str = preg_replace('/# ([^\n]*)\n/', "<h1>$1</h1>\n", $str);
    $str = preg_replace('/\[([^\]]+)\]\(([^\)]+)\)/', '<a href=\'$2\'>$1</a>', $str);
    $str = preg_replace('/([^\n\r]{2,})(?:(\r\n){2,}|\r{2,}|\n{2,}|$)/u', "<p>$1</p>\n\n", $str);
    return $str;
}

function debug($something) {
    echo "<pre><div class='debug'>\n";
    print_r($something);
    echo "\n</div></pre>\n";
}

function redirect($url) {
    session_write_close();
    header("Location: $url");
    exit();
}

function redirectRelative($url) {
    redirect(relativeURL($url));
}

function relativeUrl($url) {
    $requestURI = explode('/', $_SERVER['REQUEST_URI']);
    $scriptName = explode('/', $_SERVER['SCRIPT_NAME']);

    $dir = array();
    for ($i = 0; $i < sizeof($scriptName); $i++) {
        if ($requestURI[$i] == $scriptName[$i]) {
            $dir[] = $requestURI[$i];
        } else {
            break;
        }
    }
    return implode('/', $dir) . '/' . $url;
}

function __importTemplate($matches) {
    $fileName = $matches[1];
    if (!file_exists($fileName)) {
        die("Template $fileName doesn't exist.");
    }
    $contents = file_get_contents($fileName);
    $contents = preg_replace_callback('/%%\s*(.*)\s*%%/', '__importTemplate', $contents);
    return $contents;
}

function __resolveRelativeUrls($matches) {
    return relativeUrl($matches[1]);
}

function __cacheName($view) {
    $cachePath = explode('/', $view);
    $idx = sizeof($cachePath) - 1;
    $cachePath[$idx] = 'cache_' . $cachePath[$idx];
    return implode('/', $cachePath);
}

function renderTemplate($view, $params) {
    if (!file_exists($view)) {
        die("File $view doesn't exist.");
    }
    # do we have a cached version?
    clearstatcache();
    $cacheName = __cacheName($view);
    if (file_exists($cacheName) && (filemtime($cacheName) >= filemtime($view))) {
        $contents = file_get_contents($cacheName);
    } else {
        # we need to build the file (doesn't exist or template is newer)
        $contents = __importTemplate(array('unused', $view));

        $contents = preg_replace_callback('/@@\s*(.*)\s*@@/U', '__resolveRelativeUrls', $contents);

        // @formatter:off
        $patterns = array(
            array('src' => '/{{/', 'dst' => '<?php echo('),
            array('src' => '/}}/', 'dst' => '); ?>'),
            array('src' => '/\[\[/', 'dst' => '<?php '),
            array('src' => '/\]\]/', 'dst' => '?>')
        );
        // @formatter:on
        foreach ($patterns as $pattern) {
            $contents = preg_replace($pattern['src'], $pattern['dst'], $contents);
        }
        file_put_contents($cacheName, $contents);
    }
    extract($params);
    ob_start();
    eval("?>" . $contents);
    $result = ob_get_contents();
    ob_end_clean();
    echo $result;
}
?>