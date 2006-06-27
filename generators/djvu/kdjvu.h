/***************************************************************************
 *   Copyright (C) 2006 by Pino Toscano <toscano.pino@tiscali.it>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _KDJVU_
#define _KDJVU_

#include <qobject.h>
#include <qpixmap.h>
#include <qvector.h>

class QDomDocument;

/**
 * @brief Qt (KDE) encapsulation of the DjVuLibre
 */
class KDjVu : public QObject
{
    Q_OBJECT
    public:
        KDjVu();
        ~KDjVu();

        /**
         * A DjVu page.
         */
        class Page
        {
            friend class KDjVu;

            public:
                ~Page();

                int width() const;
                int height() const;
                int dpi() const;
                int orientation() const;

            private:
                Page();

                int m_width;
                int m_height;
                int m_dpi;
                int m_orientation;
        };

        /**
         * Opens the file \p fileName, closing the old one if necessary.
         */
        bool openFile( const QString & fileName );
        /**
         * Close the file currently opened, if any.
         */
        void closeFile();

        /**
         * The pages of the current document, or an empty vector otherwise.
         * \note KDjVu handles the pages, so you don't need to delete them manually
         * \return a vector with the pages of the current document
         */
        const QVector<KDjVu::Page*> &pages() const;

        /**
         * Get the metadata for the specified \p key, or a null string otherwise.
         */
        QString getMetaData( const QString & key ) const;

        /**
         * Get ax XML document with the bookmarks of the current document (if any).
         * The XML will look like this:
         * \verbatim
         * <!DOCTYPE KDjVuBookmarks>
         * <item title="Title 1" destination="dest1">
         *   <item title="Title 1.1" destination="dest1.1" />
         *   ...
         * </item>
         * <item title="Title 2" destination="dest2">
         * \endverbatim
         */
        const QDomDocument * documentBookmarks() const;

        // pixmap handling
        /**
         * Check if the pixmap for the specified \p page with the specified
         * \p width, \p height and \p rotation is already in cache, and returns
         * it. If not, a null pixmap is returned.
         */
        QPixmap pixmap( int page, int width, int height, int rotation );
        /**
         * Request to load the pixmap for \p page having the specified \p width,
         * \p height and \p rotation. It will emit pixmapGenerated() when done.
         */
        void requestPixmap( int page, int width, int height, int rotation );

    signals:
        /**
         * The pixmap \p pix for page \p page was generated.
         */
        void pixmapGenerated( int page, const QPixmap & pix );

    private:
        class Private;
        Private * const d;
};

#endif
