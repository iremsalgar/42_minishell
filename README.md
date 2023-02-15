# Minishell

Proje detaylarına bu linkten ulaşabilirsiniz:

[Kendi shellinizi yazmak ](https://medium.com/@iremsalgar/kendi-shell-kabu%C4%9Funuzu-yazmak-7212cec896ec)

<img width="967" alt="image" src="https://user-images.githubusercontent.com/74204825/215972090-7bfe81b1-5fc8-4cd1-a586-d7ce840f0f98.png">

## Linux Kök Dizini Nedir

Linux kök dizini (/) sistemin temel dizinidir ve tüm dosya sistemi için başlangıç noktasıdır. Bu dizin içinde bulunan dosyalar ve klasörler sistemin çalışması için gereklidir ve genellikle sistem yöneticileri tarafından yönetilir.

/bin: Bu dizinde sistem tarafından kullanılan temel komutlar bulunur. Örneğin, ls, cp, mv gibi komutlar bu dizinde yer alır.

/sbin: Sistem yöneticileri tarafından kullanılan komutları içerir. Örneğin, reboot, fdisk gibi komutlar bu dizinde yer alır.

/etc: Sistem yapılandırma dosyalarını içerir. Örneğin, network, ssh gibi yapılandırma dosyaları bu dizinde yer alır.

/dev: Sistem tarafından kullanılan cihaz dosyalarını içerir. Örneğin, /dev/sda, /dev/tty gibi cihaz dosyaları bu dizinde yer alır.

/lib ve /usr/lib: Sistem tarafından kullanılan kütüphanelerin yer aldığı dizinlerdir. Örneğin, C programları tarafından kullanılan kütüphaneler bu dizinlerde bulunur.

/var: Sistem tarafından oluşturulan ve değişebilen verilerin saklandığı dizindir. Örneğin, log dosyaları, mail gibi veriler bu dizinde yer alır.

/home: Kullanıcıların kişisel dosyalarının saklandığı dizindir. Her kullanıcının kendi dizini (örneğin /home/user) bu dizinde yer alır.

/tmp: Geçici dosyaların saklandığı dizindir. Bu dosyalar sistem tarafından kullanılmakta veya kullanıcı tarafından oluşturulmaktadır.

/root: Sistem yöneticisi (root) kullanıcısının kişisel dizinidir.

## kernel  nedir

Kernel, bir işletim sisteminin temel bileşenidir ve sistem kaynaklarının yönetimi, cihazlar arasındaki iletişim ve işletim sisteminin diğer bileşenleriyle iletişim için gerekli olan kod parçasını içerir.

Bir araba motorunun temel bileşeni olarak düşünülebilir. Motor, arabanın hareketini sağlar ve diğer parçaları (örneğin, vites kutusu, frenler) ile etkileşim içindedir. Kernel de işletim sisteminin hareketini sağlar ve diğer parçalar (örneğin, uygulamalar, cihaz sürücüleri) ile etkileşim içindedir.

## Alias Nedir

"alias" komutu, Unix ve Linux işletim sistemlerinde kullanılan bir komuttur. Bu komut, kullanıcının komut satırında yazması gereken uzun komutları kısaltmasını veya değiştirmesini sağlar. Örnekler:

Bir komutun kısaltmasını oluşturmak:
```
$ alias ll='ls -l'
```
Bu örnekte, 'll' kısaltması 'ls -l' komutu için kullanılabilir. Bu nedenle, 'll' yazmak yerine 'ls -l' yazmak gerekmez.

Bir komutun kısaltmasını kullanmak:
```
$ ll /etc
```
Bu komut, '/etc' dizinindeki dosyaların listesini 'ls -l' komutu gibi gösterir.

Bir komutun kısaltmasını silebilmek:
```
$ unalias ll
```
Bu komut ile 'll' kısaltması silinir.

Bu sadece birkaç örzeği. alias komutu ile kullanıcılar kendilerine uygun kısaltmalar veya değiştirmeler yapabilirler. Bu komutlar kullanıcının komut satırında daha hızlı ve kolay çalışmasını sağlar. Aynı zamanda, yazdığınız betikleri veya scriptleri okunaklı hale getirmek için de kullanılabilir.
