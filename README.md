# 42_minishell
Kendi (SHELL)Kabuğunuzu Yazmak
Kendi shellinizi yazmanızla ilgili bir türkçe kaynak bulamadım o nedenle izlenmesi gereken yolları burada paylaşmak istedim. Metni bir bütün olarak değil parça parça inceleyin bir çok kaynaktan her başlığa göre eklemeler yapılmıştır.
İzlenmesi gereken yollar:
1-Komut girildiğinde ve uzunluk boş değilse, geçmişte saklayın.
2-Parsing: Ayrıştırma, komutların tek tek sözcüklere ve dizelere bölünmesidir.
3-Pipe("|") vb. gibi özel karakterlerin kontrolü yapılır.
4-built-in commands
5-pipe yönlendirmeleri
6-Bir childı forklayarak ve execve'yi çağırarak sistem komutlarını ve kitaplıklarını yürütme.
7-Geçerli dizin adını yazdırma ve bir sonraki girişi isteme.
Readline
Komutların geçmişini tutmak, ok tuşlarını kullanarak geçmişi kurtarmak ve sekme tuşunu kullanarak otomatik tamamlamayı gerçekleştirmek için GNU tarafından sağlanan readline kitaplığını kullanacağız.
Readline kitaplığını kurmak için terminal penceresini açın ve yazın:
sudo apt-get install libreadline-dev
Öncelikle her yerde genişletmek kelimesini göreceksiniz bunun hakkında konuşalım:
Parametre Genişletme
Komut satırına bir komut girildiğinde, görüntülenen çıktısına genişler. Buna genişleme denir. Yazdığınız komut terminalde bulunan echo komutu yardımıyla yazdırılacaktır.
'$' karakteri, parametre genişletme, komut değiştirme veya aritmetik genişletme sunar. Genişletilecek parametre adı veya sembol, isteğe bağlı olan ancak genişletilecek değişkeni, adın bir parçası olarak yorumlanabilecek hemen ardından gelen karakterlerden korumaya yarayan ayraçlar içine alınabilir.
Parametre genişletme formatı aşağıdaki gibidir:
${ ifade }
burada ifade , '}' ile eşleşene kadar tüm karakterlerden oluşur . Bir <ters eğik çizgi> ile veya tırnak içine alınmış bir dize içinde kaçan herhangi bir '}' ve katıştırılmış aritmetik genişletmelerdeki, komut ikamelerindeki ve değişken genişletmelerdeki karakterler, '}' eşleşmesinin belirlenmesinde incelenmez .
Parametre genişletmenin en basit biçimi şudur:
${ parametre }
Varsa, parametrenin değeri değiştirilmelidir.
Parametre adı veya sembolü, birden fazla basamaklı konumsal parametreler veya parametrenin bir ad olduğu ve ardından adın bir parçası olarak yorumlanabilecek bir karakterin geldiği durumlar dışında isteğe bağlı olan ayraçlar içine alınabilir. Eşleşen kapanış ayracı, ayraç seviyelerinin sayılması, kapalı tırnaklı dizelerin üzerinden atlanması ve komut ikameleri ile belirlenecektir.
Parametre parantez içinde değilse ve bir adsa, genişletme, bu adla temsil edilen değişken var olsun ya da olmasın, en uzun geçerli adı kullanmalıdır Aksi takdirde, parametre tek karakterli bir semboldür ve bu karakter ne bir rakam ne de özel parametrelerden biri değilse davranış belirtilmez
ayrıca bakınız : https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html
PATH
PATH = işletim sistemi tarafından yürütülebilir komut dosyalarını bulmak için kullanılan değişken. Hayal ettiğiniz gibi, ls ve PATH=/usr/local/bin:/usr/bin:/bin: yaptığınızda, bu, sistemin ls adlı, ls'ye karşılık gelen yürütülebilir bir dosya arayacağı ve /usr/local dizinine bakacağı anlamına gelir. /bin bulamazsa, /usr/bin'e ve sonra /bin'e gidecektir. Bu nedenle, kullanıcı yerleşik yapılarımızda olmayan komutları yazacağı zaman, PATH'in yollarını bilmemiz gerekecek.
which # locate a command
which ls o komutun path ini verir.
The Parser
Ayrıştırıcı, "ls al" gibi komut satırını okuyan ve onu yürütülecek komutları saklayacak Komut Tablosu adı verilen bir veri yapısına yerleştiren yazılım bileşenidir.
Builtin
Dosya sisteminde herhangi bir yerde yürütülebilir bir program yerine kabuğun kendisi tarafından dahili olarak uygulanan bir komut.
The Executor
Yürütücü, çözümleyici tarafından oluşturulan komut tablosunu alacak ve dizideki her SimpleCommand için yeni bir işlem oluşturacaktır. Gerekirse, bir sürecin çıktısını bir sonrakinin girdisine iletmek için borular da oluşturur. Ek olarak, herhangi bir yeniden yönlendirme varsa standart girişi, standart çıkışı ve standart hatayı yeniden yönlendirecektir.
Aşağıdaki şekil bir komut satırını göstermektedir "A | B | C| D". Ayrıştırıcı tarafından algılanan "< infile" gibi bir yeniden yönlendirme varsa, ilk SimpleCommand A'nın girişi infile'den yönlendirilir. ">outfile" gibi bir çıktı yönlendirmesi varsa, son SimpleCommand (D) çıktısını outfile'a yönlendirir.
">& errfile" gibi bir errfile yönlendirmesi varsa, tüm SimpleCommand işlemlerinin stderr'i errfile'a yönlendirilecektir.
Kabuğunuzu tamamlayan diğer alt sistemler şunlardır:
● Environment Variables: ${VAR} biçimindeki ifadeler, karşılık gelen ortam değişkeniyle genişletilir. Ayrıca kabuk, ortam değişkenlerini ayarlayabilmeli, genişletebilmeli ve yazdırabilmelidir.
● Wildcards: a*a biçimindeki bağımsız değişkenler, yerel dizinde ve birden çok dizinde kendileriyle eşleşen tüm dosyalara genişletilir.
● Subshells: `` (ters işaretler) arasındaki bağımsız değişkenler yürütülür ve çıktı, kabuğa girdi olarak gönderilir.
GENEL BİLGİLER
Bir ayrıştırıcı(parser) iki bölüme ayrılır: Sözcüksel Çözümleyici veya Sözlükçü(Lexical Analyzer or Lexer), girdi karakterlerini alır ve karakterleri belirteç adı verilen sözcüklere bir araya getirir ve belirteçleri bir dilbilgisine göre işleyen ve komut tablosunu oluşturan bir Ayrıştırıcı.
Belirteçler(token), normal ifadeler kullanılarak bir shell.l dosyasında açıklanmıştır. Shell.l dosyası, sözcüksel çözümleyiciyi oluşturan lex adlı bir programla işlenir.
Unix benzeri sistemlerde, kabuk, çoğunlukla boşlukta bölerek, ancak aynı zamanda tırnak işaretleri ve "glob genişletme" gibi çeşitli diğer dönüşümleri de hesaba katarak komut satırından bağımsız değişkenleri tanımlar. Daha sonra bu bağımsız değişkenlerin ("argv") bir vektörünü yapar ve vektörü onları yeni oluşturulan sürece veren execve'e iletir.
Kaçış Karakteri (Ters Bölü)(Backslash)
Alıntılanmayan bir <ters eğik çizgi>, <yeni satır> dışında sonraki karakterin gerçek değerini korur. <yeni satır> <ters eğik çizgi>yi takip ederse, kabuk bunu satırın devamı olarak yorumlayacaktır. Girdi belirteçlere bölünmeden önce <ters eğik çizgi> ve <yeni satır> kaldırılacaktır. Çıkış karakterli <newline> girdiden tamamen kaldırıldığı ve herhangi bir boşlukla değiştirilmediği için belirteç ayırıcı işlevi göremez.
Tek Tırnak
Karakterleri tek tırnak ( '' ) içine almak, tek tırnak içindeki her karakterin değişmez değerini koruyacaktır. Tek tırnak içinde tek tırnak olamaz.
Çift Tırnak
Karakterleri çift tırnak ( "" ) içine almak, aşağıdaki gibi ters tırnak, <dolar-işareti> ve <ters eğik çizgi> karakterleri dışında, çift tırnak içindeki tüm karakterlerin değişmez değerini koruyacaktır:
Kapalı bir "${" ile eşleşen '}' karakter dizisi içinde , varsa, çift sayıda çıkış yapılmamış çift tırnak veya tek tırnak bulunacaktır. '{' veya '}' sabit değerinden kaçmak için öncesinde bir <ters eğik çizgi> karakteri kullanılmalıdır . Parametre Genişletmesindeki kural '}' eşleşmesini belirlemek için kullanılacaktır .
Aşağıdaki durumlardan herhangi biri tanımsız sonuçlar üretir:
"`…" dizisi içinde başlayan ancak bitmeyen tek tırnaklı veya çift tırnaklı bir dize
Aynı çift tırnaklı dize içinde başlayan ancak bitmeyen bir "`…`" dizisi

Kabuk girdisini satır cinsinden okuyacaktır. Girdi satırları sınırsız uzunlukta olabilir. Bu satırlar iki ana mod kullanılarak ayrıştırılacaktır: sıradan belirteç tanıma ve buradaki belgelerin işlenmesi.
Parser ve Lexer arasındaki fark nedir?
Symbols for the lexer: ASCII characters.
Symbols for the parser: the particular tokens, which are terminal symbols of their grammar.
Lexers attach meaning by classifying lexemes (strings of symbols from the input) as the particular tokens. E.g. All these lexemes: *, ==, <=, ^ will be classified as "operator" token by the C/C++ lexer.
Parsers attach meaning by classifying strings of tokens from the input (sentences) as the particular nonterminals and building the parse tree. E.g. all these token strings: [number][operator][number], [id][operator][id], [id][operator][number][operator][number] will be classified as "expression" nonterminal by the C/C++ parser.

<<, >>, <, >
İşaret >, bir programın çıktısını stdout'tan (varsayılan olarak terminal olan standart çıktı) başka bir şeye yönlendirmek için kullanılır.
Bir >>dosyaya ekler veya yoksa dosyayı oluşturur.
Varsa dosyanın üzerine yazar veya >yoksa oluşturur.
Her iki durumda da programın çıktısı, adı yeniden yönlendirme işlecinden sonra sağlanan dosyada saklanır.
Örnekler:
$ ls > allmyfiles.txt "allmyfiles.txt" dosyasını oluşturur ve onu ls komutundaki dizin listesiyle doldurur
$ echo "End of directory listing" >> allmyfiles.txt"allmyfiles.txt" dosyasının sonuna "Dizin listesinin sonu" ekler
$ > newzerobytefile"newzerobytefile" adıyla yeni bir sıfır bayt dosyası oluşturur veya aynı ada sahip mevcut bir dosyanın üzerine yazar (boyutu sıfır bayt yapar)
Sinyaller
Sinyalleri görmek için terminale şu komutu yazabilirsiniz:
trap -l
Kendi bash'iniz yazarken kullanmanız gereken bazı sinyaller var.
ctrl-\
ctrl-D
ctrl-C

Bu sinyaller bu dosyalardaki bazı sinyallerle eşleşiyor
SIGINT : Sinyal 2. Kullanıcı, bir işlemi kapanmaya zorlamak için Ctrl+C kombinasyonuna bastı veya komut ,kill sinyal 2 ile birlikte kullanıldı. Teknik olarak, bu bir kesme sinyalidir, bir sonlandırma sinyali değil, kesintiye uğramış bir komut dosyasıdır. sinyal işleyici genellikle sonlandırılır.
SIGQUIT : Sinyal 3. Kullanıcı, bir işlemi çıkmaya zorlamak için Ctrl+\ kombinasyonuna bastı veya killkomut, sinyal 3 ile kullanıldı.
Control-D bir sinyal göndermez, ancak girişte bir EOF (dosya sonu) belirtir.

Bash de trap nasıl çalışır:
Bash, bir komutun tamamlanmasını beklerken tuzağın kurulduğu bir sinyal aldığında, komut tamamlanana kadar tuzak yürütülmez. Bash, wait yerleşik aracılığıyla eşzamansız bir komut beklerken, tuzak ayarlanmış bir sinyalin alınması, wait yerleşikin 128'den büyük bir çıkış durumuyla hemen geri dönmesine neden olur ve hemen ardından tuzak Idam edildi.
Ctrl+D (^D) dosyanın sonu anlamına gelir. Yalnızca bir satırın başında çalışır (biraz basitleştiriyorum) ve program terminalden girdi okumuyorsa hiçbir etkisi yoktur. Deneyinizde, ^D kabuğa daha fazla komut yazmayacağınızı söyledi, bu yüzden kabuğa çıktı; daha sonra alt programı sonlandırıldığı için terminalden çıkıldı. Ctrl+C (^C) "kes" anlamına gelir, yani yaptığınız şeyi durdurun. Teknik olarak, ^C'ye basmak, varsayılan olarak bir uygulamayı sonlandıran, ancak birçok programda en üst düzeye geri dönmek anlamına gelen INT sinyalini gönderir (örneğin, bir kabukta, komut satırı yazmayı bırakın ve bozulmamış bir komut istemine geri dönün). Bir program ^C'ye yanıt vermiyorsa, Ctrl+\ (^\)'yi deneyebilirsiniz. Bu, varsayılan olarak bir uygulamayı sonlandıran ve çok fazla programın araya girmediği QUIT sinyalini gönderir.
Komutlar için Çıkış Durumu
Her komutun, diğer kabuk komutlarının davranışını etkileyebilecek bir çıkış durumu vardır. Yardımcı program olmayan komutların çıkış durumu bu bölümde belgelenmiştir. Standart yardımcı programların çıkış durumu, ilgili bölümlerinde belgelenmiştir.
Bir komut bulunamazsa çıkış durumu 127 olacaktır. Komut adı bulunursa ancak çalıştırılabilir bir yardımcı program değilse çıkış durumu 126 olacaktır. Yardımcı programları kabuk kullanmadan çağıran uygulamalar bu çıkış durumu değerlerini kullanmalıdır. benzer hataları bildirmek için.
Kelime genişletme veya yeniden yönlendirme sırasında bir komut başarısız olursa, çıkış durumu sıfırdan büyük olacaktır.
Dahili olarak, bir komutun sıfırdan farklı bir çıkış durumuyla çıkıp çıkmadığına karar vermek amacıyla, kabuk, wait () işlevi WEXITSTATUS makrosunun (Sistem Arayüzleri biriminde tanımlandığı gibi ) eşdeğeri tarafından komut için alınan tüm durum değerini tanıyacaktır. IEEE Std 1003.1–2001). Çıkış durumunu '?' özel parametresiyle bildirirken , kabuk mevcut tam sekiz bitlik çıkış durumunu rapor edecektir. Sinyal aldığı için sonlandırılan bir komutun çıkış durumu 128'den büyük olarak rapor edilmelidir.
Pipe()
Pipe, bir işletim sisteminde iki veya daha fazla program arasında veri akışını sağlamak için kullanılan bir mekanizmadır. Pipe, bir programın çıktısını başka bir programın girdisi olarak kullanmasını sağlar. C dilinde, "pipe()" fonksiyonu kullanılarak pipe oluşturulur.
Aşağıdaki örnekte, "ls -l" komutunun çıktısı "grep root" komutunun girdisi olarak kullanılmaktadır:
#include <stdio.h>
#include <unistd.h>
int main() {
    int fd[2];
    pipe(fd); // pipe oluşturulur
    if (fork() == 0) {
        // Çocuk işlem
        close(fd[0]); // okuma ucunu kapat
        dup2(fd[1], 1); // yazma ucunu standart çıktıya yönlendir
        execlp("ls", "ls", "-l", NULL);
    } else {
        // Ana işlem
        close(fd[1]); // yazma ucunu kapat
        dup2(fd[0], 0); // okuma ucunu standart girdiye yönlendir
        execlp("grep", "grep", "root", NULL);
    }
    return 0;
}
Bu örnekte, "pipe()" fonksiyonu ile pipe oluşturuldu ve "fork()" fonksiyonu ile iki işlem oluşturuldu. Çocuk işlem, "ls -l" komutunun çıktısını pipe'ın yazma ucuna yazdı ve ana işlem ise pipe'ın okuma ucundan "grep root" komutunun girdisi olarak verileri aldı.
Ayrıca, "dup2()" fonksiyonu kullanılarak standart çıktı ve girdi yönlendirmeleri yapılmıştır. Bu fonksiyon, verilen dosya tanımlayıcısını standart çıktı veya girdi tanımlayıcısına yönlendirir
Kavramsal olarak Pipe, iki süreç arasındaki bir bağlantıdır, öyle ki bir sürecin standart çıktısı diğer sürecin standart girdisi olur.
UNIX İşletim Sisteminde, Pipelar ilgili süreçler arasındaki iletişim (işlemler arası iletişim) için kullanışlıdır.
Kanal, oluşturma işlemi ve onun tüm alt işlemleri tarafından okuma ve yazma için kullanılabilir. Bir proses bu "sanal dosyaya" veya kanala yazabilir ve diğer ilgili proses ondan okuyabilir
fd[0], için fd(dosya tanıtıcı) olacaktır. borunun ucunu oku.
fd[1], borunun yazma ucu için fd olacaktır.
Pipelar FIFO (İlk Giren İlk Çıkar) gibi davranır, Pipe bir kuyruk veri yapısı gibi davranır.
Okuma ve yazma boyutunun burada eşleşmesi gerekmez.
Bir seferde 512 bayt yazabiliriz ama bir Pipe da bir seferde sadece 1 bayt okuyabiliriz.
Herhangi bir işlemde çatal kullandığımızda, dosya tanımlayıcıları alt süreçte ve ayrıca üst süreçte açık kalır.
Pipe oluşturduktan sonra fork çağırırsak ebeveyn ve çocuk pipe üzerinden haberleşebilir.
EXECVE()
int execve(const char *path, char *const argv[], char *const envp[]);
Yürütücü işlevler ailesi, mevcut işlem görüntüsünü yeni bir işlem görüntüsüyle değiştirecektir. Yeni görüntü, yeni işlem görüntü dosyası adı verilen normal, yürütülebilir bir dosyadan oluşturulmalıdır . Çağıran işlem görüntüsü yeni işlem görüntüsü tarafından kaplandığı için başarılı bir exec'den geri dönüş olmayacaktır .
execve() kullanma
Aşağıdaki örnek, bağımsız değişkenleri cmd dizisindeki ls komutuna iletir ve env bağımsız değişkenini kullanarak yeni işlem görüntüsü için ortamı belirtir .
#include <unistd.h>
int ret;
char *cmd[] = { "ls", "-l", (char *)0 };
char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };
...
ret = execve ("/bin/ls", cmd, env);
execve neden envp argümanı alır:
execve() fonksiyonu, çalıştırmak istediğiniz programın çalışma ortamını belirlemek için envp (environment pointer) argümanını alır. envp, ortam değişkenlerinin tutulduğu bir dizidir. Ortam değişkenleri, programın çalışması sırasında erişebileceği bilgileri içerir, örneğin PATH değişkeni, sistemin hangi klasörlerinde programlar aranacağını belirtir ve HOME değişkeni, kullanıcının ev dizininin nerede olduğunu belirtir. Bu değişkenler, execve() fonksiyonu tarafından çalıştırılacak programa geçirilir ve programın çalışması sırasında bu bilgilere erişmesine izin verir.
Süreç Nedir?
Yazdığımız programlar, bir bilgisayar tarafından yürütülmesi amaçlanan talimat ve işlemler dizisidir. Bir program ve tüm dosyaları bir sabit sürücüye kaydedilir ve kendi başına hiçbir şey yapmaz.
İster bir kabuk komutuyla, ister bir simgeye çift tıklayarak veya başlangıçta otomatik olarak bir programı çalıştırdığımızda, sistem komutlarını RAM'e yükler ve birbiri ardına yürütür. Bu yürütme durumundaki bir program, süreç olarak adlandırdığımız şeydir .
Sabit sürücüde bir program var; RAM'de bir işlem var.
İşletim sistemi tüm işlemleri yönetir ve her birine bir bellek alanı tahsis eder. Her birinin kendi yığını, kendi yığını, kendi yönerge işaretçisi vb. vardır. Bu, bir işlemin başka bir işlemin belleğine veya yönergelerine kolayca erişemeyeceği anlamına gelir. Bu nedenle her süreç ayrı bir varlıktır.
Aşağıdaki komut ile terminalimizdeki kabuk programının hem PID'sini hem de PPID'sini kontrol edebiliriz:
$ echo "PID = $$; PPID = $PPID"
Böylece süreçler, aşağıdakilerle bir hiyerarşide düzenlenir:
alt süreçler yaratan ana süreçler ,
üst süreçleri tarafından oluşturulan ve karşılığında kendi alt süreçlerini oluşturabilen alt süreçler .

fork()
fork () negatif bir değer döndürürse, alt sürecin oluşturulması başarısız olmuştur.
fork() , yeni oluşturulan alt sürece sıfır döndürür.
fork() , ebeveyne alt sürecin işlem kimliği olan pozitif bir değer döndürür . Döndürülen işlem kimliği, sys/types.h içinde tanımlanan pid_t türündedir . Normalde işlem kimliği bir tamsayıdır. Ayrıca, bir işlem, bu işleme atanan işlem kimliğini almak için getpid() işlevini kullanabilir.

fork() çağrısı başarılı bir şekilde yürütülürse, Unix
biri ebeveyn, diğeri çocuk için olmak üzere adres alanlarının iki özdeş kopyasını oluşturun.
Her iki işlem de yürütmeye fork() çağrısını izleyen bir sonraki ifadede başlayacaktır . Bu durumda, her iki süreç de aşağıda gösterildiği gibi atama deyiminde yürütmeye başlayacaktır:

Her iki işlem de sistem çağrısı fork() 'tan hemen sonra yürütmeye başlar . Her iki işlem de aynı fakat ayrı adres alanlarına sahip olduğundan , fork() çağrısından önce başlatılan bu değişkenler , her iki adres alanında da aynı değerlere sahiptir. Her işlemin kendi adres alanı olduğundan, herhangi bir değişiklik diğerlerinden bağımsız olacaktır. Başka bir deyişle, ebeveyn değişkeninin değerini değiştirirse, değişiklik sadece ebeveyn sürecin adres alanındaki değişkeni etkiler. fork() çağrıları tarafından oluşturulan diğer adres alanları , aynı değişken adlarına sahip olsalar bile etkilenmeyecektir.
printf yerine write kullanılmasının nedeni nedir ? Bunun nedeni, printf() 'in "ara belleğe alınmış" olmasıdır, yani printf() bir işlemin çıktısını birlikte gruplandıracaktır. Ana süreç için çıktıyı arabelleğe alırken, çocuk aynı zamanda arabelleğe alınacak bazı bilgileri yazdırmak için printf'i kullanabilir. Sonuç olarak çıktı ekrana hemen gönderilmeyeceği için beklenen sonucun doğru sırasını alamayabilirsiniz. Daha da kötüsü, iki sürecin çıktıları tuhaf şekillerde karışabilir. Bu sorunun üstesinden gelmek için "arabelleğe alınmamış" yazma özelliğini kullanmayı düşünebilirsiniz .
Ebeveyn ve Çocuk Süreçlerini Ayırmak
Çocuk, ebeveynin bir klonu olduğu için, tam olarak aynı koda sahip olacaktır. Ancak, muhtemelen çocuğa ebeveyninden farklı talimatlar vermek istiyoruz. Sistem forkçağrısının bir tamsayı türü olan dönüş değeri, pid_tebeveyne ve çocuğa aynı PID'yi döndürmez. Yani onları ayırt etmek için kullanacağımız şey bu. İşte forkfonksiyonun olası dönüş değerleri:
ebeveyn çocuğun PID'sini alır,
çocuk 0 alır,
ve bir hata durumunda fork-1 döndürür.

Yani fork'un dönüş değeri olarak 0'ı görürsek, çocuk süreçte olduğumuzu anlarız. Aksi takdirde bir PID görürsek, ebeveynde olduğumuzu biliriz.
Wait ve Waitpid Sistem Çağrıları
Bu sistem çağrılarının tümü, çağıran sürecin bir çocuğundaki durum değişikliklerini beklemek ve durumu değişen çocuk hakkında bilgi almak için kullanılır. Durum değişikliği şu şekilde kabul edilir: çocuk sonlandırıldı; çocuk bir sinyalle durduruldu; veya çocuk bir sinyalle devam ettirildi. Sonlandırılan bir çocuk durumunda, bekleme gerçekleştirmek, sistemin çocukla ilişkili kaynakları serbest bırakmasına izin verir; bir bekleme gerçekleştirilmezse ve sonlandırılırsa, çocuk bir "zombi" durumunda kalır.
wait () sistem çağrısı , çocuklarından biri sona erene kadar mevcut sürecin yürütülmesini askıya alır.
waitpid () sistem çağrısı , pid bağımsız değişkeni tarafından belirtilen bir alt öğe durumu değiştirene kadar geçerli işlemin yürütülmesini askıya alır . Varsayılan olarak, waitpid () yalnızca sonlandırılan çocukları bekler, ancak bu davranış, aşağıda açıklandığı gibi seçenekler bağımsız değişkeni aracılığıyla değiştirilebilir.
Ana sürecin yürütmesini alt sürecin durumu değişene kadar askıya almak için kütüphaneden waitveya waitpidsistem çağrılarını kullanabiliriz. <sys/wait.h>Prototipleri:
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
İkisi arasındaki fark, özellikle bir sürecin birkaç çocuğu olduğunda fark edilir. Arama wait, sonlandırılan ilk alt öğeyi alırken waitpid, belirttiğimiz PID ile eşleşen alt öğeyi tutar ve diğerlerinin tümünü yok sayar. Ayrıca, waitpidbirkaç seçenek belirlememizi sağlar.
Her iki sistem çağrısı için ortak parametre şudur:
statuswait : ve waitpidçocuğun çıkış durumunu depolayabilen bir tamsayı türü değişkenine işaretçi . Diğer şeylerin yanı sıra, çocuğun normal bir şekilde bitirip bitirmediğini veya kesintiye uğrayıp uğramadığını belirlemek için bu sayıyı farklı makrolarla inceleyebileceğiz.

öğesinin iki ekstra parametresi waitpidaşağıdaki gibidir:
pid : Beklememiz gereken alt sürecin PID'si. Ana süreç bu PID'yi bilir çünkü bu fork, çocuk oluşturulduğunda sağlanan dönüş değeridir. Alternatif olarak, hangi çocuğun önce bitirdiğini beklemek için -1 belirtebiliriz, tıpkı wait(aslında, waitpid(-1, status, 0)ile tamamen aynıdır wait(status).)
seçenekler : waitpidbirkaç seçenek sunar. Bunlar arasında bazen çok yararlı olan WNOHANG. WNOHANGSeçeneği ile , waitpidalt süreç henüz bitmemişse hemen geri döner. Bu seçenek olmadan, çocuk görevlerini yürütmeye devam ettiği sürece ana süreç varsayılan olarak askıda kalacaktır.

Sistem çağrısı başarılı olursa, her ikisi waitde waitpidsonlandırılan çocuğun PID'sini döndürür, aksi takdirde -1 döndürür. Seçenek belirtilmişse ve beklediği çocuk henüz durum değiştirmemişse, işlev waitpid0 değerini de döndürebilir .WNOHANG
Zombiler
Zombi = sona ermiş ancak ebeveyni henüz onu beklememiş bir süreç
Zombileri görmenin bir yolu Ctrl-Z, yürütmenin ortasında (askıya al) düğmesine basmak ve ardından bir pskomut girmektir. Zombiler <defunct> süreçler olarak görünür.

Ya waitda waitpidzombileri kaldırmak için kullanılabilir.
wait(ve waitpidengelleme biçiminde), bir alt işlem çalışırken bir üst işlemin yürütülmesini geçici olarak askıya alır. Çocuk bittiğinde, bekleyen ebeveyn yeniden başlatılır.
#include <sys/types.h>
    #include <sys/wait.h>
pid_t bekle(int *statloc);
    /* Tamamsa işlem kimliğini veya hata durumunda -1'i döndürür */
    pid_t waitpid(pid_t pid, int *statloc, int seçenekler);
    /* işlem kimliğini döndürür : tamamsa, 
    * 0 : engellemesiz seçenek && etrafta zombi yoksa 
    * -1 : hata durumunda 
    */
Argüman statlociki değerden biri olabilir:
NULL işaretçisi: bağımsız değişken basitçe göz ardı edilir
bir tamsayı işaretçisi: wait geri döndüğünde, bunun tanımladığı tamsayı, sonlandırılan sürecin durum bilgisini içerecektir (sonlandırma durumunu inceleyen makrolar için bkz. Stevens s.198)

wait()waitpid()waitbir alt süreç sona erene kadar arayanı engeller
waitpidengelleyici veya engelleyici olmayabilir:
Seçenekler 0 ise , o zaman engelliyor
Seçenekler WNOHANG ise , bloke olmaz mı?

birden fazla çocuk çalışıyorsa wait(), ebeveynin yavrularından birinin ilk çıkışında geri döner
waitpiddaha esnektir:
pid == -1 ise , herhangi bir alt süreci bekler. Bu bakımdan waitpideşdeğerdirwait
pid > 0 ise , işlem kimliği pid'e eşit olan çocuğu bekler
pid == 0 ise , süreç grubu kimliği çağıran sürecinkine eşit olan herhangi bir alt öğeyi bekler.
pid < -1 ise , işlem grubu kimliği pid'in mutlak değerine eşit olan herhangi bir alt öğeyi bekler

Bir Alt Sürecin Çıkış Durumunu Analiz Etme
ve işlevleri bize wait, waitpidbir alt sürecin yürütülmesini tamamlama şekli hakkında birçok bilgi içeren bir durum sağlar. Durum, yalnızca çıkış kodunu değil, aynı zamanda bir çocuğun çıkış nedenini açıklayan diğer ayrıntıları da temsil eden bir tamsayıdır. Böylece bir çocuğun tüm görevlerini gerçekten bitirip bitirmediğini veya yarıda kesilip kesilmediğini kolayca anlayabiliriz.
Birkaç makro sayesinde durumu inceleyebiliriz:
WIFEXITED(status): çocuk normal bir şekilde sonlandırıldıysa, örneğin exit çağırarak veya programın ana işlevini bitirerek true değerini döndürür.
WEXITSTATUS(status): yalnızca WIFEXITEDtrue olarak döndürülürse kullanılacaktır. Çocuğun çıkış kodunu, yani çocuğun çıkış işlevinde veya ana işlevin dönüşünde belirttiği sayıyı döndürür.
WIFSIGNALED(status): alt öğe bir sinyal tarafından zorla sonlandırıldıysa true değerini döndürür .
WTERMSIG(status): yalnızca WIFSIGNALEDtrue olarak döndürülürse kullanılacaktır. Çocuğun sonlandırılmasına neden olan sinyal numarasını döndürür.

kill: Alt Süreçleri Sonlandırma
int kill(pid_t pid, int sig);
Tedarik etmemiz gereken parametreler:
pid : Öldürmek istediğimiz sürecin PID'si.
sig : Sürece onu öldürmek için göndermek istediğimiz sinyal. Öldürme için birçok farklı olası sinyal vardır, her birinin kendi nüansları vardır (bkz. adam 7 sinyali ), ancak en sık kullanılanlar belki SIGTERM(yumuşak sonlandırma sinyali) ve SIGKILL(sert öldürme sinyali)'dir.

killişlevleri başarı için 0 ve başarısızlık için -1 döndürür.
chdir()
chdir komutu , geçerli çalışma dizinini değiştirmek için kullanılan bir sistem işlevidir (sistem çağrısı). Bazı sistemlerde bu komut, cd kabuk komutunun diğer adı olarak kullanılır . chdir, çağıran işlemin geçerli çalışma dizinini yol içinde belirtilen dizine değiştirir.
Sözdizimi:
int chdir(const char *yol);
Parametre: Buradaki yol , kullanıcının mevcut çalışma dizini yapmak istediği Dizin yoludur.
Dönüş Değeri: Bu komut, başarı durumunda sıfır (0) döndürür. Bir hata durumunda -1 döndürülür ve errno uygun şekilde ayarlanır.
Readline için çevirisi çok kötü olsanada bunları bıramak istiyorum:
https://web.mit.edu/gnu/doc/html/rlman_2.html
bu siteden bakabilirsiniz.
işlev: int rl_redisplay ()
Geçerli içeriğini yansıtmak için ekranda görüntülenenleri değiştirin rl_line_buffer.
işlev: int rl_forced_update_display ()
Readline ekran görüntüsünün doğru olduğunu düşünse de düşünmese de satırı güncellenmeye ve yeniden görüntülenmeye zorlar.
işlev: int rl_on_new_line ()
Güncelleme yordamlarına, genellikle yeni bir satır çıktısı aldıktan sonra yeni (boş) bir satıra geçtiğimizi söyleyin.
işlev: int rl_reset_line_state ()
Görüntü durumunu temiz duruma sıfırlayın ve mevcut satırı yeni bir satırdan başlayarak yeniden görüntüleyin.
işlev: int rl_message (va_alist)
Argümanlar, sağlanacağı gibi bir dizedir printf. Ortaya çıkan dize, yankı alanında görüntülenir . Yankı alanı ayrıca sayısal bağımsız değişkenleri ve arama dizelerini görüntülemek için kullanılır.
işlev: int rl_clear_message ()
Yankı alanındaki mesajı temizleyin.
Bu yazıda bir çok başlığa bir çok siteden değindik. Ancak Eklenmesi gereken daha çok şey olduğuna eminim. O nedenle bu yazıyı sık sık güncelleyeceğim böylece sonunda tamamlanmış. Bu başlıkları araştırarak kendi shellinizi yazabilirsiniz.
