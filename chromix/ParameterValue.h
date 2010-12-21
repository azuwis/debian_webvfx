// Copyright (c) 2010 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMIX_PARAMETERVALUE_H_
#define CHROMIX_PARAMETERVALUE_H_

#include <string>
#include <third_party/WebKit/JavaScriptCore/wtf/RefCounted.h>
#include <third_party/WebKit/JavaScriptCore/wtf/text/WTFString.h>
#include <third_party/WebKit/WebCore/html/ImageData.h>

namespace v8 {
    template <class T> class Handle;
    class Value;
}

namespace Chromix {

class ImageParameterValue {
public:
    ImageParameterValue() {};
    ImageParameterValue(WTF::PassRefPtr<WebCore::ImageData> value) : imageData(value) {};
    ~ImageParameterValue() {};

    WebCore::ImageData* getValue() const { return imageData.get(); }
    v8::Handle<v8::Value> getV8Value() const;

private:
    WTF::RefPtr<WebCore::ImageData> imageData;
};


class ParameterValue : public WTF::RefCounted<ParameterValue>  {
public:
    virtual v8::Handle<v8::Value> getV8Value() const = 0;
protected:
    friend class WTF::RefCounted<ParameterValue>;
    ParameterValue() {};
    virtual ~ParameterValue() {};
};

template <typename T>
class PrimitiveParameterValue : public ParameterValue  {
public:
    PrimitiveParameterValue(const T& value) : value(value) {};
    const T getValue() const { return value; }
    virtual v8::Handle<v8::Value> getV8Value() const = 0;
private:
    T value;
};


class StringParameterValue : public PrimitiveParameterValue<WTF::String> {
public:
    static WTF::PassRefPtr<StringParameterValue> create(const WTF::String& value) { return adoptRef(new StringParameterValue(value)); }
    static WTF::PassRefPtr<StringParameterValue> create(const std::string& value) { return create(WTF::String::fromUTF8(value.data(), value.size())); }
    virtual v8::Handle<v8::Value> getV8Value() const;

private:
    StringParameterValue(const WTF::String& value) : PrimitiveParameterValue<WTF::String>(value) {};
};


class BooleanParameterValue : public PrimitiveParameterValue<bool> {
public:
    static WTF::PassRefPtr<BooleanParameterValue> create(bool value) { return adoptRef(new BooleanParameterValue(value)); }
    virtual v8::Handle<v8::Value> getV8Value() const;

private:
    BooleanParameterValue(bool value) : PrimitiveParameterValue<bool>(value) {};
};


class NumberParameterValue : public PrimitiveParameterValue<double> {
public:
    static WTF::PassRefPtr<NumberParameterValue> create(double value) { return adoptRef(new NumberParameterValue(value)); }
    virtual v8::Handle<v8::Value> getV8Value() const;

private:
    NumberParameterValue(double value) : PrimitiveParameterValue<double>(value) {};
};

}

#endif

