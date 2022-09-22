/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACELITE_FRAMEWORK_MIN_JS_H
#define OHOS_ACELITE_FRAMEWORK_MIN_JS_H

// AUTO GENERATED, PLEASE DO NOT EDIT DIRECTLY

#ifndef ACELITE_FRAMEWORK_RAW_BUFFER
#error THIS FILE CAN ONLY BE INCLUDED BY RAW BUFFER CPP
#endif

#ifndef OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER
#define OHOS_ACELITE_FRAMEWORK_MIN_JS_BUFFER
const char * const g_frameworkJSBuffer =
    "!function(t,e){'object'==typeof exports&&'undefined'!=typeof module?module.exports=e():'fun"
    "ction'==typeof define&&define.amd?define(e):(t=t||self).ViewModel=e()}(this,(function(){'u"
    "se strict';var t={stack:[],push:function(t){this.stack.push(t)},pop:function(){return this"
    ".stack.pop()},top:function(){return this.stack[this.stack.length-1]}},e=function(t){return"
    "'object'==typeof t&&null!==t},n=function(t,e,n){Object.defineProperty(t,e,{enumerable:!1,v"
    "alue:n})};function i(t,e,n,i){this._ctx=t,this._getter=e,this._fn=n,this._meta=i,this._las"
    "tValue=this._get()}function o(e){this._hijacking=!0,n(e,'__ob__',this),Array.isArray(e)&&f"
    "unction(t){Object.setPrototypeOf(t,s)}(e),Object.keys(e).forEach((function(n){return funct"
    "ion(e,n,i){var r=e.__ob__;Object.defineProperty(e,n,{enumerable:!0,get:function(){var e=t."
    "top();e&&e.subscribe(r,n);var s=o.of(i);return o.is(s)&&s.setParent(r,n),i},set:function(t"
    "){i=t,r.notify(n)}})}(e,n,e[n])}))}i.prototype._get=function(){try{return t.push(this),thi"
    "s._getter.call(this._ctx)}finally{t.pop()}},i.prototype.update=function(){var t=this._last"
    "Value,n=this._get(),i=this._ctx,o=this._meta;(n!==t||e(n))&&(this._fn.call(i,n,t,o),this._"
    "lastValue=n)},i.prototype.subscribe=function(t,e){var n=t.attach(e,this);'function'==typeo"
    "f n&&(this._detaches||(this._detaches=new Set),this._detaches.add(n))},i.prototype.unsubsc"
    "ribe=function(){var t=this._detaches;t&&(t.forEach((function(t){t()})),this._detaches.clea"
    "r())},o.of=function(t){return t&&e(t)?t.__ob__?t.__ob__:new o(t):t},o.is=function(t){retur"
    "n t&&t._hijacking},o.prototype.attach=function(t,e){if(void 0!==t&&e){this._obsMap||(this."
    "_obsMap={}),this._obsMap[t]||(this._obsMap[t]=new Set);var n=this._obsMap[t];return n.add("
    "e),function(){n.delete(e)}}},o.prototype.notify=function(t){void 0!==t&&this._obsMap&&this"
    "._obsMap[t]&&this._obsMap[t].forEach((function(t){return t.update()}))},o.prototype.setPar"
    "ent=function(t,e){this._parent=t,this._key=e},o.prototype.notifyParent=function(){this._pa"
    "rent&&this._parent.notify(this._key)};var r=['push','pop','unshift','shift','sort','splice"
    "','reverse'],s=Object.create(Array.prototype);function c(t){if(!(this instanceof c))return"
    " new c(t);var e=this._vm=this;'[object Object]'===Object.prototype.toString.call(t)&&Objec"
    "t.keys(t).forEach((function(n){var i=t[n];'render'===n?e.$render=i:'data'===n?function(t,e"
    "){'function'==typeof e&&(e=e.call(t,t));Object.keys(e).forEach((function(n){return functio"
    "n(t,e,n){Object.defineProperty(t,n,{enumerable:!1,configurable:!0,get:function(){return e["
    "n]},set:function(t){e[n]=t}})}(t,e,n)})),o.of(e)}(e,i):'styleSheet'===n?initStyleSheet(i):"
    "'function'==typeof i&&(e[n]=i.bind(e))}))}return r.forEach((function(t){var e=s[t];n(s,t,("
    "function(){var n,i=Array.prototype.slice.call(arguments);e.apply(this,i),'push'===t||'unsh"
    "ift'===t?n=i:'splice'===t&&(n=i.slice(2)),n&&n.length&&n.forEach(o.of);var r=this.__ob__;r"
    "&&r.notifyParent()}))})),c.prototype.$watch=function(t,e,n){return new i(this,t,e,n)},c}))"
    ";";
#endif
#endif // OHOS_ACELITE_FRAMEWORK_MIN_JS_H
