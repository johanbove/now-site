<?php
class Custom_Filters extends \Twig\Extension\AbstractExtension
{

    public function getFilters()
    {
      return [
        /**
         * base64_encode => name of custom filter,
         * base64_en => name of function to execute when this filter is called.
         */
        new \Twig\TwigFilter('base64_encode', array($this, 'base64_en')),
        new \Twig\TwigFilter('base64_decode', array($this, 'base64_dec')),
        new \Twig\TwigFilter('parseLinks', array($this, 'parse_as_link'), ['is_safe' => ['html']]),
        new \Twig\TwigFilter('longDateStamp', array($this, 'render_date')),
        new \Twig\TwigFilter('shortDateStamp', array($this, 'render_date_short')),
        new \Twig\TwigFilter('sortByUrgency', array($this, 'sortByUrgency')),
      ];
    }

    public function base64_en($input)
    {
       return base64_encode($input);
    }

    public function base64_dec($input)
    {
        return base64_decode($input);
    }

    /**
     * Parse a string links as an HTML clickable link
     * @see <https://daringfireball.net/2010/07/improved_regex_for_matching_urls>
     */
    public function parse_as_link(string $string)
    {
      $pattern = "/(?i)\b((?:https?:\/\/|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}\/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'\".,<>?«»“”‘’]))/";
      return preg_replace($pattern, "<a href=\"$1\">$1</a>", $string);
    }

    /**
     * Outputs give date in specific format
     * @see <https://blog.serverdensity.com/handling-timezone-conversion-with-php-datetime/>
     */
    public function render_date(string $date, string $format = 'D, j\<\s\u\p\>S<\/\s\u\p\> M Y \a\t H:i:s')
    {
      $userTimezone = new DateTimeZone('Europe/Berlin');
      $gmtTimezone = new DateTimeZone('GMT');
      $myDateTime  = new DateTime($date, $gmtTimezone);
      $offset = $userTimezone->getOffset($myDateTime);
      $myInterval=DateInterval::createFromDateString((string)$offset . 'seconds');
      $myDateTime->add($myInterval);
      $formatedTime = $myDateTime->format($format);
      return $formatedTime;
    }

    public function render_date_short(string $string)
    {
      return $this->render_date($string, 'Y-m-d H:i:s');
    }

    /**
     * @see https://stackoverflow.com/a/13792558
     */
    private function sort_arr_of_obj($array, $sortby, $direction='asc')
    {

      $sortedArr = array();
      $tmp_Array = array();

      // var_dump($array);

      foreach ($array as $k => $v) {
        $tmp_Array[] = $v[$sortby];
      }

      if ($direction == 'asc') {
        asort($tmp_Array);
      } else {
        arsort($tmp_Array);
      }

      foreach ($tmp_Array as $k => $tmp) {
          $sortedArr[] = $array[$k];
      }

      return $sortedArr;
    }

    public function sortByUrgency(array $array)
    {
      return $this->sort_arr_of_obj($array, 'urgency', 'desc');
    }

}
