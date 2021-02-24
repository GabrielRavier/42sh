/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares randomd
*/

#pragma once

#include <math.h>
#include <float.h>

// Obtained from various sources, some really random floats, then some data from bionic, then floating point limits
static const long double RANDOM_FLOATS[] = {
    0.0014329879003995,
    0.0029808110086022,
    0.008845529776087l,
    0.0098676133724017l,
    0.011936806277212,
    0.019864559648594,
    0.0226924644414,
    0.023569890093547,
    0.025260742456297,
    0.030262709490251,
    0.032261095268908l,
    0.034734338587833,
    0.034859470622526,
    0.041323363234381,
    0.041812541945544,
    0.041951469999439l,
    0.041952456715928,
    0.042563438445232,
    0.044339240381409l,
    0.054145564519934l,
    0.056778115039961,
    0.057833431919296,
    0.059884783053813l,
    0.064764445744822,
    0.065586758637685l,
    0.072037425988317,
    0.075013446177113,
    0.075165115216589,
    0.075532673831724,
    0.075599405946218,
    0.076355778690677,
    0.077433225839149l,
    0.078300720354776l,
    0.078807675817493l,
    0.080092314063301,
    0.080792769689019,
    0.081165983428923l,
    0.081944077796422,
    0.083962999408897,
    0.084232373036848,
    0.085982351467099l,
    0.086212514535305l,
    0.08977889971396,
    0.090554219936473,
    0.092024062101607,
    0.092141557518028l,
    0.094148642087901,
    0.095311017455661,
    0.096656876300772,
    0.10035655413113,
    0.10179691720465,
    0.10189905501489l,
    0.10235362675232,
    0.10423239846404,
    0.10459129484924,
    0.10597978154524,
    0.10667431991292,
    0.10706522806141,
    0.10776530210435,
    0.10894205689646,
    0.113002092461l,
    0.11664603387419,
    0.12025768743424,
    0.12148065594945,
    0.12231353525883,
    0.12273520729795,
    0.12310712725777,
    0.12429346240475,
    0.12505768614941,
    0.12536899977789l,
    0.12537259329522,
    0.12554120780494,
    0.12741231017463,
    0.13056745538932,
    0.13133312518441,
    0.13150559747959l,
    0.13177305511323,
    0.13326955766868,
    0.13425629848357,
    0.13640774401079,
    0.13642219643048,
    0.13840559448265,
    0.13922000822484l,
    0.14228751171025,
    0.14330510377954,
    0.14895774190846,
    0.14910601164128,
    0.15105011749836l,
    0.15237420476689l,
    0.152743777613,
    0.15312368569394,
    0.15484454553396,
    0.15716644446285,
    0.15762031567436,
    0.15780574958794,
    0.15796497608829,
    0.15963028538944l,
    0.16388289585472,
    0.1644051378146,
    0.16685592643099,
    0.1674574296474l,
    0.16909646601727,
    0.17029931281652,
    0.17340512667028,
    0.17418717445806,
    0.17481030578392,
    0.17790346627099,
    0.17984351918563,
    0.18214406667807,
    0.18520828649735,
    0.19170483674637,
    0.19300001443747,
    0.19520042873804l,
    0.19733923247316l,
    0.19895269712361l,
    0.19900153077324,
    0.19955222882927,
    0.19980201603184,
    0.1999294948072l,
    0.19998678721629,
    0.20170302267437,
    0.20376380011394l,
    0.20678123435841,
    0.20834635209692l,
    0.20850559638968,
    0.20976270347335,
    0.21101680077685,
    0.21204051168265l,
    0.21248351710268l,
    0.21426084772081,
    0.21454490404431,
    0.21462360988716,
    0.21474098080569,
    0.21706108725052,
    0.21811484703021l,
    0.21855116653599,
    0.21954372267682,
    0.22351061264917,
    0.22564447065654,
    0.22607292340535,
    0.22608425738518,
    0.2275039117849,
    0.22798266158005l,
    0.22823807669872l,
    0.22857848844403l,
    0.22976588662861,
    0.22997421137701,
    0.23018145783489l,
    0.23037947211126,
    0.23197956859731,
    0.23350770996421,
    0.23400550969122,
    0.23423890049191,
    0.23970770506477l,
    0.24065479640988,
    0.2423437534178,
    0.24283880783559,
    0.24488661684203,
    0.24661449653506l,
    0.24787483251361l,
    0.24978561636478,
    0.24994286577341l,
    0.2504891355167,
    0.25052786705509,
    0.25121110393933,
    0.25142895430426l,
    0.25485995970285,
    0.25532405455686,
    0.25685574736352l,
    0.25745209049418,
    0.25762733786152,
    0.25813324728945,
    0.25892275022212l,
    0.25994052598594,
    0.26186261817527,
    0.26293723751531l,
    0.26351904510917l,
    0.26382944447444,
    0.2644591496379,
    0.26449490453957,
    0.26488193025449l,
    0.26832435025124,
    0.26930401464547,
    0.27394280546002,
    0.27774042878497,
    0.27823118960516,
    0.27911838336159,
    0.28152295732091l,
    0.28160701484021,
    0.28171300069944,
    0.28243322262274,
    0.28297927120346,
    0.28338269289533l,
    0.28339900191062l,
    0.28378368373219,
    0.28476149524079l,
    0.28528353049979,
    0.28756341639588,
    0.28814024722164l,
    0.29245164210589,
    0.29268055852006,
    0.29277418151544,
    0.293305689315,
    0.29426693993936,
    0.29457182645464,
    0.2964418215977,
    0.29730226544565,
    0.29849604179846,
    0.29969083396593,
    0.29982712522368l,
    0.30096063915518,
    0.30233081111062l,
    0.30303267193642,
    0.30356314292814l,
    0.30372401768677l,
    0.30420319679192,
    0.3056115218801,
    0.30613403467123l,
    0.30689711194815,
    0.30963598701345,
    0.31006181907193,
    0.31008963486201l,
    0.31157524843039,
    0.31212992360562,
    0.31412634539356l,
    0.31520508179058,
    0.3171693428975l,
    0.31755999873614l,
    0.31832442554343l,
    0.31973512439782l,
    0.32051615106829l,
    0.32057352142106,
    0.32170706473958,
    0.32248945898658l,
    0.32327481774524,
    0.32354700439549,
    0.32379393534343,
    0.32426693503416,
    0.32481004501241,
    0.32626738960336,
    0.32806551781042,
    0.32828565979049,
    0.32834203736905,
    0.32893737852792,
    0.3291510548257,
    0.32974818368055,
    0.33291481536917,
    0.33548643873208l,
    0.33554046208621,
    0.33863271956196,
    0.34081120038026,
    0.3415326499541l,
    0.34175094849484,
    0.34222374101949,
    0.34638527117286,
    0.34657712338241,
    0.34688999720153l,
    0.34695522157591l,
    0.34714541169245,
    0.34741896625005l,
    0.34800560970517l,
    0.34880491266664l,
    0.34903339035348l,
    0.35128054751665,
    0.35186961146415,
    0.35192547105136l,
    0.35203431179201l,
    0.3521711153,
    0.35229458776596l,
    0.3530020718386,
    0.3531824856865,
    0.3538077668937l,
    0.35457467330411,
    0.35516953235199,
    0.35647881868196l,
    0.35685581779833,
    0.35719214206841,
    0.36022723364522,
    0.36114737331567l,
    0.36157205788507,
    0.36214433098451,
    0.36252771372461,
    0.36555079160856,
    0.36763469462226,
    0.36858060333659,
    0.36968116726505l,
    0.3705452673639,
    0.37080715488099l,
    0.37139224288323,
    0.37220624683231,
    0.37327564874281,
    0.3740273483979,
    0.37441958344677,
    0.37461399460254l,
    0.37462316884388,
    0.37669538977481,
    0.37692522415435,
    0.37714394820021,
    0.37755042704752,
    0.37884598255695,
    0.37928181158473,
    0.37939198720497,
    0.37971157516303,
    0.38010491527963,
    0.38015009710415l,
    0.38123596920888,
    0.38130267156535,
    0.38277261593098,
    0.38343827073983,
    0.38387062133065l,
    0.38491445961768,
    0.38581360195168l,
    0.38591958741546,
    0.38666520392211,
    0.3869537414601l,
    0.38821923915997,
    0.38846883184861,
    0.38876382816782,
    0.38964704992288,
    0.39144647725118,
    0.39249310824502,
    0.39384023563941,
    0.39419561040414,
    0.39460237366781l,
    0.39463951630203,
    0.39464680423809l,
    0.39479796826923,
    0.39575855715702,
    0.3960013033618l,
    0.39601342941694,
    0.39704450819588l,
    0.39845098935398l,
    0.39850628025885,
    0.39979122006324,
    0.40049532785381l,
    0.40129988127912,
    0.4020971716247,
    0.40389833076553,
    0.40617862836598,
    0.40703346171402,
    0.40769107669874l,
    0.40787479668154,
    0.4086419179384l,
    0.40989890622959,
    0.4105292963028,
    0.41091122857294,
    0.41098163975212,
    0.41134529477113,
    0.41147908551961,
    0.4116730482718l,
    0.41212069916352,
    0.41323594403801,
    0.41385394583078,
    0.41408079902982,
    0.41419295408319,
    0.4142532091822,
    0.41511486605251,
    0.41583629902238,
    0.41678168792101l,
    0.41719321738708,
    0.41819209440635,
    0.41821304800758,
    0.41944544679636,
    0.4199390035536,
    0.42067760196644,
    0.42095656797272,
    0.42138852613417,
    0.42171144689426,
    0.4217407618113l,
    0.42192189448937,
    0.42329020366511,
    0.42386485532735,
    0.42597035140297,
    0.42605666278562,
    0.42641304210902,
    0.42733329011052,
    0.42797472139291l,
    0.4280642906421l,
    0.42943046443378l,
    0.42971631609189,
    0.42990621382819,
    0.43017072973755,
    0.43088681555164,
    0.43261241772554,
    0.43314339455143,
    0.43416608179237,
    0.43453004538575,
    0.43540326420357l,
    0.4355399320313,
    0.43593128664822,
    0.43643797533282,
    0.43658350266097,
    0.43728674846438,
    0.43757825988078,
    0.43784987480572,
    0.43797107543096,
    0.43811878489538,
    0.4384900591465,
    0.43876362094595,
    0.43881140253175,
    0.44143842173096,
    0.44197300830233,
    0.44217206527945,
    0.44249358365064,
    0.44306688235393,
    0.44448113747268,
    0.44455578644332,
    0.44557359603417,
    0.44599099964243,
    0.44609142176177,
    0.44720740390856,
    0.4475973608353,
    0.44779596645368,
    0.44840744180667l,
    0.44863173301307,
    0.44968359426658,
    0.4498841254886,
    0.45105714400953,
    0.45108255945196,
    0.451219120935,
    0.45134398195357l,
    0.4532853042398,
    0.45383924678779,
    0.45406528035725,
    0.45456860692513,
    0.4551765661254,
    0.455597656362,
    0.45569126867787l,
    0.45625633796176,
    0.45674470097193l,
    0.45690271582069,
    0.45759586186567,
    0.45778773859306,
    0.45866437842459,
    0.45868779686784,
    0.45887062475115l,
    0.46099280334738,
    0.46121805573549,
    0.46135759990919,
    0.46165521594185,
    0.46195336108812,
    0.46260426732298,
    0.46311253518476,
    0.46333679218942,
    0.46361191982903,
    0.46371331616369l,
    0.46461685200192,
    0.46603964526411l,
    0.46630506055486,
    0.46801970895706,
    0.46862420049286,
    0.4688308119565,
    0.47045796217751,
    0.47082548919242l,
    0.4710243514579,
    0.47114175694864,
    0.47176188468089,
    0.47309747554677,
    0.47320788361247,
    0.47374132798455,
    0.47468459239404,
    0.47516698561158l,
    0.47518744812236,
    0.4756401699583,
    0.47617260699595,
    0.47714034054634l,
    0.47780006995743l,
    0.47958722836785,
    0.47987919343835,
    0.48056163116672,
    0.48178841933629,
    0.4821775757567,
    0.48258061420436,
    0.48305940364594,
    0.48375717362741,
    0.48463236526011,
    0.48650740959159,
    0.48707029868962,
    0.48713904150718l,
    0.48854254369338,
    0.48977509665879l,
    0.49004648410077,
    0.49006192344383l,
    0.49083262497705l,
    0.4910210008457,
    0.49120773259468l,
    0.49207406309772,
    0.49234683129646,
    0.49298084326148,
    0.49358442557037,
    0.49497361092917l,
    0.49500073062881l,
    0.49500275422384,
    0.49590764917244,
    0.49645792381166,
    0.4966193185009,
    0.49775699246664,
    0.49778932751094,
    0.4978374378186,
    0.49861662351245,
    0.49994274043817,
    0.50007745097234,
    0.50027240227192l,
    0.50073514563993,
    0.50205008011022,
    0.50308857260217,
    0.50321489319486,
    0.50387853526455l,
    0.50429820697398,
    0.50472219751582,
    0.50479452580396,
    0.50507630964687,
    0.50550635211954,
    0.50609236549647,
    0.50679151976606l,
    0.50780271846546,
    0.50821302484927,
    0.5084640729211,
    0.50856698531917,
    0.50889970502795,
    0.50890904390602,
    0.50897518650603l,
    0.50936089458902l,
    0.50946899869181l,
    0.50990173627012,
    0.51061890808803,
    0.5107762831679,
    0.51159820787959,
    0.51218994314412,
    0.51247254128503,
    0.51255763938224,
    0.51281313071451,
    0.51314571899887,
    0.51360091862006,
    0.51562856234477l,
    0.51566398307373l,
    0.51716896536965l,
    0.51756101097374,
    0.51762987552693,
    0.51824592767529,
    0.51831647104772l,
    0.51882964671103,
    0.52054898397052,
    0.52065040173987,
    0.52146994418503,
    0.52159990511339,
    0.52161583707678l,
    0.52170816686069,
    0.5225160918011,
    0.5233024538488,
    0.52331945362576,
    0.52405100916255,
    0.52434407821092,
    0.52609236303021,
    0.52625155418655,
    0.52711212047201,
    0.52726111139571,
    0.52799144002846,
    0.52842995155449l,
    0.52919397795509l,
    0.53007405100045,
    0.53087792880921,
    0.5311317826673l,
    0.5312268076903,
    0.53266660040497,
    0.53272276071321,
    0.53282017644496,
    0.53292208990039l,
    0.53344977085996,
    0.53405868470984l,
    0.53457263951458,
    0.53555875774923,
    0.53605744954901,
    0.53650040631025l,
    0.53686147903823,
    0.53695187249382,
    0.5386130970145,
    0.53907468861404,
    0.53921345650396,
    0.54024050232054,
    0.5410459625133,
    0.54125856703243l,
    0.54134967954338l,
    0.54146324190743l,
    0.54169198546484,
    0.5421562735653l,
    0.54350098567319l,
    0.54369142982626,
    0.54436763601256l,
    0.54441625351355l,
    0.54486657219795,
    0.5454324793582,
    0.54631178017899,
    0.54641567683953,
    0.54668057482429,
    0.54734789483409,
    0.54848723289481,
    0.54948208002551,
    0.55091141415935,
    0.55114758499521,
    0.55235500931489l,
    0.55239923047213l,
    0.55262551246654,
    0.55262566616817l,
    0.55271098483668,
    0.55355873945271,
    0.55365986428873,
    0.55375676676098,
    0.55393454055733,
    0.55430829205876,
    0.55454917904138l,
    0.55469808530709,
    0.55534135445523,
    0.55563434456012l,
    0.55651188055065,
    0.55738901572532,
    0.5592035723494,
    0.56051188689655,
    0.56059233027461l,
    0.5607117182824l,
    0.56146583721301l,
    0.56224199320715,
    0.56286328114815,
    0.56356523787985,
    0.56364521498626,
    0.56449270408708,
    0.56484340085763,
    0.565739298298,
    0.56856233530033,
    0.56933164491701,
    0.56968025519282,
    0.56998474048835,
    0.57058510852504l,
    0.57061522706239l,
    0.57243702452053,
    0.57269999106568,
    0.57355950678016l,
    0.57450011806052l,
    0.57458092925843,
    0.57532228599903l,
    0.57621735420935l,
    0.57720255202745l,
    0.57918507398873l,
    0.58060243999895,
    0.5812139216579,
    0.58201140105815,
    0.58216829418415,
    0.58275855631121l,
    0.58372210250977,
    0.58381906778637,
    0.58557932506945,
    0.58696411077606,
    0.58696448846668,
    0.58739186101814,
    0.58879893196827,
    0.58896125994545,
    0.58907795979717,
    0.59000890007453l,
    0.59032093559462,
    0.59253707816522l,
    0.59455674199331,
    0.59470200848888,
    0.59471669323413,
    0.59558136900929l,
    0.59586591466482l,
    0.59617685134042,
    0.59763670336612,
    0.59773915721374,
    0.59828306766339,
    0.59852494326814,
    0.59932698704602l,
    0.59965903200457,
    0.60025195968793,
    0.60045042436522,
    0.60053625872961,
    0.60101668279607,
    0.60251606326349,
    0.60253183701667,
    0.60284400454531,
    0.60313815575767,
    0.60412440101369,
    0.60443462627214,
    0.60531145108594,
    0.60542563689529,
    0.60554699027596,
    0.60705647185037,
    0.60796912520875,
    0.60893888844968,
    0.60905120966904,
    0.60921975003908,
    0.61282610234512,
    0.61367042060881l,
    0.61483498067928,
    0.61666090726128,
    0.61672813709143,
    0.61753561626272l,
    0.61806025898988,
    0.61898691409559,
    0.62281353568712l,
    0.62412688606228,
    0.62425210592233,
    0.62435513577739,
    0.62550308126725,
    0.62635435746129,
    0.6271413955765l,
    0.62814742854948,
    0.62875473200649l,
    0.62962527899029,
    0.63065092567941,
    0.63183624608511l,
    0.63225463100838,
    0.63243964634835,
    0.63505553037792,
    0.63530083205399,
    0.63652635376503,
    0.63774602718255,
    0.63924546422015,
    0.63942527362863,
    0.63978821745788l,
    0.64056534412284,
    0.64102570604986,
    0.64210526029215,
    0.64465751012398,
    0.64557028799589l,
    0.64652361976781,
    0.64690548454005,
    0.64764346424118,
    0.64828526148538l,
    0.65203014329868,
    0.65356738246005,
    0.65400498100306,
    0.65467851744441,
    0.65574507987548l,
    0.6560691915564,
    0.65651236939011,
    0.65737747459937,
    0.65756500133164,
    0.6587658536049,
    0.65960926371617,
    0.66025429803072l,
    0.66173001547008,
    0.66306932206475,
    0.66313937044537,
    0.66359235789455,
    0.66452466512603,
    0.66586358835327,
    0.66698019096307,
    0.66704130104675,
    0.66733540956584,
    0.66875062582638,
    0.668956999666,
    0.66946729071109l,
    0.66979599989924,
    0.66994577264534,
    0.6705830612069l,
    0.67142679652567l,
    0.67198748027878,
    0.67224726727261l,
    0.67281463681271,
    0.67285763931263l,
    0.67611763580785,
    0.67735585606146,
    0.67774157227931,
    0.67832259661809,
    0.67833292669444,
    0.67984218780631,
    0.68183752386149,
    0.68332693749106,
    0.68335930733121,
    0.68484656074033,
    0.68503546611687,
    0.68543203133647l,
    0.69034102538589,
    0.69215053887821,
    0.69354928123235,
    0.69827439748259,
    0.69886073287783,
    0.69981089211854,
    0.70016262554669l,
    0.70084425214047,
    0.70127467735486,
    0.70172458856297,
    0.70273474659005l,
    0.70275953557871,
    0.70282229203226,
    0.70315328022588,
    0.70671530805184,
    0.70679439076449l,
    0.70708906531134,
    0.70716288026538,
    0.70736039984825l,
    0.70785858665448l,
    0.70837091162596,
    0.70997654960706,
    0.71159532746423l,
    0.71307480292248l,
    0.71326576967404,
    0.71500549247277,
    0.7155459612367,
    0.71690056231175,
    0.71765024177173,
    0.7182774892279,
    0.71995902378639,
    0.7244880560613l,
    0.7254799454733l,
    0.72558139034522l,
    0.72770681156597,
    0.72991951024396,
    0.73125362963479,
    0.7318298370004l,
    0.73184425065296l,
    0.73204470880325,
    0.73466838410123,
    0.73512842346517l,
    0.73611403014953,
    0.73763499615163l,
    0.73914306820921,
    0.73977877362355,
    0.74122394770638,
    0.74126791348794,
    0.74312680631525,
    0.74338743104945l,
    0.74471365493628,
    0.74616645634872,
    0.74731898101949,
    0.74758283725817l,
    0.74970418149046,
    0.75060514171974,
    0.75171465237819,
    0.75297391179584,
    0.75542708199283,
    0.75592011412268,
    0.75658861364108,
    0.75741758855465l,
    0.7575443034266l,
    0.75770419707194,
    0.75951535941664,
    0.76132853122874,
    0.76234337583833,
    0.76312025888814,
    0.76421191215817,
    0.7663150394976l,
    0.76724925917068,
    0.76914397870755,
    0.76929390643279,
    0.77008732706384,
    0.77139376105444l,
    0.77404895055843,
    0.77803033087615,
    0.78247461818932,
    0.78280825670129,
    0.78295472473931,
    0.7842944542813,
    0.78460715028906,
    0.78668460795323,
    0.78847358772182l,
    0.78873891525293,
    0.79238592307152,
    0.79459362825388,
    0.79560087947779,
    0.79631807655193,
    0.79724313706931l,
    0.79926871168498,
    0.80093506386273,
    0.80581803118295,
    0.80720776607151,
    0.80728659115007,
    0.80966282067516,
    0.81208143297052,
    0.81211660665717,
    0.81329625822126,
    0.81434844769599,
    0.81444937392941,
    0.81497934609539,
    0.81617095683367,
    0.8175095793793,
    0.82120974318576,
    0.82335075568197,
    0.82478349077538l,
    0.82690350089958,
    0.82805109145582l,
    0.8291503384155,
    0.82958878776978,
    0.83122263981865l,
    0.83139167548381,
    0.8320122479418l,
    0.83243349648283,
    0.83258594416944,
    0.83404991259704,
    0.8353427862207,
    0.83735850039197,
    0.83808549278662l,
    0.84363891345238,
    0.8443616976497l,
    0.84567298031815,
    0.84673967576278,
    0.85016819705193l,
    0.85337961634907,
    0.85564736551897,
    0.85597961198458,
    0.85611293001821l,
    0.85723419619242,
    0.85790135392121,
    0.85845485454485l,
    0.85973291366152,
    0.86038740836343,
    0.86043741787067,
    0.86287787536818,
    0.86432136340415,
    0.86508028200621,
    0.86600790886953,
    0.86916890523213,
    0.87003846783717,
    0.87138278907762,
    0.87180207313567l,
    0.87229285057663,
    0.87456327128045,
    0.87481381498298,
    0.87723681537202,
    0.87729693711997,
    0.88266596068568l,
    0.88446401568556,
    0.88731086233901,
    0.88898559590135,
    0.88953930407023,
    0.88961437905402,
    0.88998069925518,
    0.89128120464237,
    0.89328264694846,
    0.89435054756906,
    0.89711966280472,
    0.89780111506396,
    0.90006440424354l,
    0.90250710650215,
    0.90273708779891,
    0.90401834002675,
    0.90428315561894,
    0.90864968547802,
    0.90893177146297l,
    0.91241670704566,
    0.91337259145553,
    0.91673122847613,
    0.917611998438,
    0.92227232766178,
    0.92229653522552,
    0.92505787435187,
    0.92520278493531,
    0.92596093280762l,
    0.92773543504507l,
    0.92797587627813l,
    0.92853753391742l,
    0.93070897368967,
    0.9320543807205,
    0.93687051339881,
    0.93884893875438,
    0.93930225397189,
    0.94032677511188,
    0.94079209615333,
    0.9436778935643,
    0.94516086385498l,
    0.94624521455386,
    0.94625030865672l,
    0.94735543767058,
    0.94829038127554l,
    0.94933578789487,
    0.94951042002595,
    0.95199742041604,
    0.95300636060665,
    0.95519233838373,
    0.95634302821116,
    0.95811686845163,
    0.9608470430888,
    0.96376216734709,
    0.96416811920297,
    0.96740115782236,
    0.96852706762491,
    0.96880794693068l,
    0.97021295143126,
    0.97076140241802,
    0.97158312600895,
    0.97297470766042,
    0.97429174447209,
    0.97445768130978,
    0.97487288563621,
    0.97606763016737,
    0.97607059259438,
    0.9802586242948,
    0.98071820223617,
    0.98148202547769,
    0.98250304271507l,
    0.98361076613755,
    0.98380087556157l,
    0.9853620109874l,
    0.98688977549053l,
    0.99604090346903,
    0.9965232281009,
    0.99722353358446,
    0.99749302975057,
    0.9995066553175,
    0.99992462281876l,
    -.0l,
    .0l,
    0x1.00000000000010p0,
    0x1.00000000000010p-1,
    0x1.00000000000010p1,
    0x1.00000000000010p-10,
    0x1.00000000000010p10,
    0x1.00000000000010p-100,
    0x1.00000000000010p100,
    0x1.00000000000010p-1000,
    0x1.00000000000010p1000,
    0x1.00000000000010p-1022,
    0x1.00000000000010p-15,
    0x1.00000000000010p15,
    0x1.00000000000010p-2,
    0x1.00000000000010p2,
    0x1.00000000000010p-20,
    0x1.00000000000010p20,
    0x1.00000000000010p-200,
    0x1.00000000000010p200,
    0x1.00000000000010p-3,
    0x1.00000000000010p3,
    0x1.00000000000010p-4,
    0x1.00000000000010p4,
    0x1.00000000000010p-5,
    0x1.00000000000010p5,
    0x1.00000000000010p-7,
    0x1.00000000000010p7,
    0x1.00000000000010p-9,
    0x1.00000000000010p9,
    -0x1.0000000000001p0,
    0x1.0000000000001p0,
    0x1.0000000000001p-1,
    0x1.0000000000001p1,
    0x1.0000000000001p-10,
    0x1.0000000000001p10,
    0x1.0000000000001p-100,
    0x1.0000000000001p100,
    0x1.0000000000001p-1000,
    -0x1.0000000000001p-1022,
    0x1.0000000000001p-1022,
    0x1.0000000000001p-15,
    0x1.0000000000001p15,
    0x1.0000000000001p-2,
    0x1.0000000000001p2,
    0x1.0000000000001p-20,
    0x1.0000000000001p20,
    0x1.0000000000001p-200,
    0x1.0000000000001p200,
    0x1.0000000000001p-3,
    0x1.0000000000001p3,
    0x1.0000000000001p-4,
    0x1.0000000000001p4,
    0x1.0000000000001p-5,
    0x1.0000000000001p5,
    0x1.0000000000001p-7,
    0x1.0000000000001p7,
    0x1.0000000000001p-9,
    0x1.0000000000001p9,
    -0x1.0p0,
    0x1.0p0,
    0x1.0p-1,
    0x1.0p1,
    0x1.0p-10,
    0x1.0p10,
    0x1.0p-100,
    0x1.0p100,
    0x1.0p-1000,
    -0x1.0p-1022,
    0x1.0p-1022,
    -0x1.0p-1073,
    0x1.0p-1073,
    -0x1.0p-1074,
    0x1.0p-1074,
    0x1.0p-15,
    0x1.0p15,
    0x1.0p-2,
    0x1.0p2,
    0x1.0p-20,
    0x1.0p20,
    0x1.0p-200,
    0x1.0p200,
    0x1.0p-3,
    0x1.0p3,
    0x1.0p-4,
    0x1.0p4,
    0x1.0p-5,
    0x1.0p5,
    0x1.0p-7,
    0x1.0p7,
    0x1.0p-9,
    0x1.0p9,
    0x1.921fb54442d180p0,
    0x1.921fb54442d180p-1,
    0x1.921fb54442d180p1,
    -0x1.921fb54442d18p0,
    0x1.921fb54442d18p0,
    -0x1.921fb54442d18p-1,
    -0x1.921fb54442d18p1,
    0x1.921fb54442d18p-1,
    0x1.921fb54442d18p1,
    0x1.ffffffffffffc0p-1023,
    -0x1.ffffffffffffcp-1023,
    0x1.ffffffffffffcp-1023,
    0x1.ffffffffffffe0p-1023,
    0x1.ffffffffffffe0p1023,
    -0x1.ffffffffffffep-1023,
    -0x1.ffffffffffffep1023,
    0x1.ffffffffffffep-1023,
    0x1.ffffffffffffep1023,
    0x1.fffffffffffff0p0,
    0x1.fffffffffffff0p-1,
    0x1.fffffffffffff0p1,
    0x1.fffffffffffff0p-10,
    0x1.fffffffffffff0p-1001,
    0x1.fffffffffffff0p-101,
    0x1.fffffffffffff0p1023,
    0x1.fffffffffffff0p-11,
    0x1.fffffffffffff0p14,
    0x1.fffffffffffff0p-16,
    0x1.fffffffffffff0p19,
    0x1.fffffffffffff0p199,
    0x1.fffffffffffff0p-2,
    0x1.fffffffffffff0p2,
    0x1.fffffffffffff0p-201,
    0x1.fffffffffffff0p-21,
    0x1.fffffffffffff0p-3,
    0x1.fffffffffffff0p3,
    0x1.fffffffffffff0p-4,
    0x1.fffffffffffff0p4,
    0x1.fffffffffffff0p-5,
    0x1.fffffffffffff0p-6,
    0x1.fffffffffffff0p6,
    0x1.fffffffffffff0p-8,
    0x1.fffffffffffff0p8,
    0x1.fffffffffffff0p9,
    0x1.fffffffffffff0p99,
    0x1.fffffffffffff0p999,
    0x1.fffffffffffffp0,
    -0x1.fffffffffffffp-1,
    0x1.fffffffffffffp-1,
    0x1.fffffffffffffp1,
    0x1.fffffffffffffp-10,
    0x1.fffffffffffffp-1001,
    0x1.fffffffffffffp-101,
    -0x1.fffffffffffffp1023,
    0x1.fffffffffffffp1023,
    0x1.fffffffffffffp-11,
    0x1.fffffffffffffp14,
    0x1.fffffffffffffp-16,
    0x1.fffffffffffffp19,
    0x1.fffffffffffffp199,
    0x1.fffffffffffffp-2,
    0x1.fffffffffffffp2,
    0x1.fffffffffffffp-201,
    0x1.fffffffffffffp-21,
    0x1.fffffffffffffp-3,
    0x1.fffffffffffffp3,
    0x1.fffffffffffffp-4,
    0x1.fffffffffffffp4,
    0x1.fffffffffffffp-5,
    0x1.fffffffffffffp-6,
    0x1.fffffffffffffp6,
    0x1.fffffffffffffp-8,
    0x1.fffffffffffffp8,
    0x1.fffffffffffffp9,
    0x1.fffffffffffffp99,
    0x1.p0,
    0x1.p-1,
    0x1.p1,
    0x1.p-10,
    0x1.p10,
    0x1.p-100,
    0x1.p100,
    0x1.p-1000,
    0x1.p1000,
    0x1.p-1022,
    0x1.p-1073,
    0x1.p-1074,
    0x1.p-15,
    0x1.p15,
    0x1.p-2,
    0x1.p2,
    0x1.p-20,
    0x1.p20,
    0x1.p-200,
    0x1.p200,
    0x1.p-3,
    0x1.p3,
    0x1.p-4,
    0x1.p4,
    0x1.p-5,
    0x1.p5,
    0x1.p-7,
    0x1.p7,
    0x1.p-9,
    0x1.p9,
    -100.5l,
    -100.l,
    100.l,
    38.l,
    -4.9406564584124654e-324l,
    4.9406564584124654e-324l,
    -5.l,
    5.l,
    -.6l,
    .6l,
    -DBL_EPSILON,
    DBL_EPSILON,
    -DBL_MAX,
    DBL_MAX,
    -DBL_MIN,
    DBL_MIN,
    -DBL_TRUE_MIN,
    DBL_TRUE_MIN,
    -FLT_EPSILON,
    FLT_EPSILON,
    -FLT_MAX,
    FLT_MAX,
    -FLT_MIN,
    FLT_MIN,
    -FLT_TRUE_MIN,
    FLT_TRUE_MIN,
    -HUGE_VALF,
    HUGE_VALF,
    -HUGE_VAL,
    HUGE_VAL,
    -HUGE_VALL,
    HUGE_VALL,
    -INFINITY,
    INFINITY,
    -LDBL_EPSILON,
    LDBL_EPSILON,
    -LDBL_MAX,
    LDBL_MAX,
    -LDBL_MIN,
    LDBL_MIN,
    -LDBL_TRUE_MIN,
    LDBL_TRUE_MIN,
    -NAN,
    NAN,
    -__builtin_nansf(""),
    __builtin_nansf(""),
    -__builtin_nans(""),
    __builtin_nans(""),
    -__builtin_nansl(""),
    __builtin_nansl(""),
    3.141l,
    3.141e30l,
    3.141e-30l,
    -2.718l,
    -2.718e30l,
    -2.718e-30l,
    0.0l,
    1.l,
    -3.l,
    __builtin_nanf(""),
    __builtin_nan(""),
    __builtin_nanl(""),
    __FLT_DENORM_MIN__,
    __DBL_DENORM_MIN__,
    __LDBL_DENORM_MIN__,
};
