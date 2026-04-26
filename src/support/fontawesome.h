#pragma once

#include <QFont>
#include <QIcon>

namespace font_awesome {

QFont fa_font();
QFont fa_brands_font();
QIcon icon(const QChar& code, const QColor& color);
QIcon icon(const QChar& code);
QIcon brand(const QChar& code, const QColor& color);
QIcon brand(const QChar& code);

} // namespace font_awesome

#define FA_FONT font_awesome::fa_font()
#define FAB_FONT font_awesome::fa_brands_font()
#define FA_ICON(code) font_awesome::icon(QChar{code})
#define FA_ICON_COLOR(code, color) font_awesome::icon(QChar{code}, color)
#define FAB_ICON(code) font_awesome::brand(QChar{code})
#define FAB_ICON_COLOR(code, color) font_awesome::brand(QChar{code}, color)
