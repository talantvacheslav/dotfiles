const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#0d0d0d", /* black   */
  [1] = "#7D8188", /* red     */
  [2] = "#8B8E95", /* green   */
  [3] = "#989BA3", /* yellow  */
  [4] = "#9EA1A7", /* blue    */
  [5] = "#ACAEB4", /* magenta */
  [6] = "#B9BCC2", /* cyan    */
  [7] = "#d6d7da", /* white   */

  /* 8 bright colors */
  [8]  = "#959698",  /* black   */
  [9]  = "#7D8188",  /* red     */
  [10] = "#8B8E95", /* green   */
  [11] = "#989BA3", /* yellow  */
  [12] = "#9EA1A7", /* blue    */
  [13] = "#ACAEB4", /* magenta */
  [14] = "#B9BCC2", /* cyan    */
  [15] = "#d6d7da", /* white   */

  /* special colors */
  [256] = "#0d0d0d", /* background */
  [257] = "#d6d7da", /* foreground */
  [258] = "#d6d7da",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
