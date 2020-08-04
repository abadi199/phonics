/**
 * Welcome to your Workbox-powered service worker!
 *
 * You'll need to register this file in your web app and you should
 * disable HTTP caching for this file too.
 * See https://goo.gl/nhQhGp
 *
 * The rest of the code is auto-generated. Please don't update this file
 * directly; instead, make changes to your Workbox build configuration
 * and re-run your build process.
 * See https://goo.gl/2aRDsh
 */

importScripts("https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

workbox.core.skipWaiting();

workbox.core.clientsClaim();

/**
 * The workboxSW.precacheAndRoute() method efficiently caches and responds to
 * requests for URLs in the manifest.
 * See https://goo.gl/S9QRab
 */
self.__precacheManifest = [
  {
    "url": "icons-192.2c93dd15.png",
    "revision": "08ec3c675c9ebb7768b0f74fa4d53503"
  },
  {
    "url": "icons-512.ce4204bd.png",
    "revision": "54a57b893094e432383379e3fe9c742d"
  },
  {
    "url": "index.html",
    "revision": "dede01adb5ee23ff7048378be8991351"
  },
  {
    "url": "src.faab5ea6.js",
    "revision": "e78e28e0c4b24d2cca8acc47dc8830c0"
  },
  {
    "url": "style.f980779d.css",
    "revision": "b8bbbd8d130a444d6fcb00cc752c77bf"
  },
  {
    "url": "/phonics/",
    "revision": "ec009be1971f6759707878c0dd844488"
  }
].concat(self.__precacheManifest || []);
workbox.precaching.precacheAndRoute(self.__precacheManifest, {});

workbox.routing.registerNavigationRoute(workbox.precaching.getCacheKeyForURL("./index.html"));
