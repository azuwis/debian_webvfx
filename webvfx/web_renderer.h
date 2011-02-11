// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBVFX_WEB_RENDERER_H_
#define WEBVFX_WEB_RENDERER_H_

#include <QObject>
#include <QSize>
#include <QUrl>
#include "webvfx/web_effects.h"
#include "webvfx/web_image.h"

namespace WebVFX
{

class WebImage;
class WebPage;
class WebParameters;

class WebRenderer : public QObject, public WebEffects
{
    Q_OBJECT
public:
    WebRenderer();
    ~WebRenderer() {};

    bool initialize(const std::string& url, int width, int height, WebParameters* parameters = 0);
    const ImageTypeMap& getImageTypeMap();
    WebImage getImage(const std::string& name, int width, int height);
    const WebImage render(double time, int width, int height);
    void destroy();

private:
    Q_INVOKABLE void initializeInvokable(const QUrl& url, const QSize& size, WebParameters* parameters);
    Q_INVOKABLE void renderInvokable(double time, const QSize& size);

    // Test if we are currently on the UI thread
    bool onUIThread();

    WebPage* webPage;
    WebImage renderImage;
    bool loadResult;
};

}

#endif