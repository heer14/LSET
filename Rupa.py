#!/usr/bin/python
# -*- coding: <<encoding>> -*-
#-------------------------------------------------------------------------------
#   <<project>>
#
#-------------------------------------------------------------------------------

import wx, wx.html
import sys

guide = """<p><h1>Hey Rupa</h1></p><p>Rupa , I am giving this to you , so that even if I may not be with you physically , I can be there with you in all your different moods.</p><p>Please select your current meed from 'Mood' tab :) </p><p>with lots of love, </p><p>Yours heer</p> """
aboutText = """<p>Just for letting """

HappyText = """<p><h1>hey Baby ,</p><p> I am so glad that you are happy :) , because it makes me happy when you are happy! <p></p>your smile is very precious for me.</p><p>I don’t know what it is that made you so happy, but I hope you will be always happy like this</p>. <p>I know you’ve been kind of low the past few weeks and I know that you really needed this up. </p><p>I love you yaaar ! I hope everything you’ve been hoping for happens, and that you keep that lovely smile on your face (: I love your smile a lot :) </p>
<p>only Yours , </p><p>Heer</p>"""


SadText = """ <p><h1>hey Rupa </h1></p><p>I hope you don’t have to read this one for a very long time, and I hope when you do it’s not because of me.even if it is becasuse of me , I want you to remember that I love you nd your smile makes me smile</p><p>pleas smile for me. whatever it is that’s got you down, you can get around it.</p><p> you’re stronger than anything trying to bring you down. I love you to pieces, and I’m always here to talk to, even if you’re in tears or in your worst state. I love you so so much.
<p> go listen to music, take a nap, <B>call me if you need</b>, whatever you need to do to get that smile back.
<p>If you are sad becose of me and you need reminder how much I love you please select reminder note </p>
<p><b><I>I love you the most when you’re happy. but I’ll love you no matter what.</i></b></p><p>only Yours , </p><p>Heer</p>"""

ReminderText = """<p><h1>Hey Love</h1></p> <p>I hope you never have to open this letter.But still if any time comes when you need a reminder How much I love you , please read This letter.</p><p>Baby , Only person that crosses my mind, when I’m sad, is You,and if that’s not love I don’t know what is.</p><p> Even When I’m alone, I think of the times , when you hold me in your arms all night long.</p><p>when I think about how you’ve stayed by me through all of my bull shit, I fall for you even harder.</p><p> Without you I wouldn’t be who I am today.</p><p> Without you, I’d be so much colder, and I don’t think I’d have even a idea of what love really is.</p><p> I love you. and when I say I love you, i mean it. </p><p>I love every single thing about you.I love you when you are mad at me , I love you when you are at your worst, I love you when you are behaving rude ,Baby I love all of you. Your flaws, physical and mental, everything about you.</p><p><b> I love you so so much, and never forget that.</b>
<p>Madly in Love with you  , </p><p>Heer</p>"""

laughText = """<p><h1>Hey My Love</h1></p><p> I think we have a problem here , I can't stop thinking about you and I think ,I am addicted to you. Anyways ,If you need a good laugh , </p><p><b>Just think of my face when I cry :P </b></p>If this is not working then ,  I want you to open this link : </a href = " "> Yours_Heer </a> </p> <p> I hope now you have that cute smile back :) I love you rupa <p>Yours crazy ,  </p><p>Heer</p>"""

LonelyText= """<p><h1>hello there :) </h1></p><p>Baby I want to remind you that - <b><i>I am yours and I will be always with you no matter what</i></b></p><p> I want you to remember that people around you cares for you. If you are feeling lonely , Just give me a call : +917046299304 , I am here for you always.</p><p> baby , As long as you have me in your life , you will never be alone , you will always have a semi-wife(or wife someday :P ) , who is always be there by your side :) </p><p>So now , smile , because , my smile depends on yours :) </p><p>P.s : You can give me a video call also, I will always be here.<p></p> And if for some reason I am not available at this moment , just remember I AM YOURS ans you will always find me standing right next to you no matter what :)</p><p>your's wify , </p><p>Heer</p>"""

BreakUPText = """<p><h1>Hi rupa</h1></p>I hope you will never have to read this letter ever. But Deep down inside I know you will need to read this one many times :( .I have given so many reason for break Up and I know even if you are with me , somewhere you are still angry for so many reasons :< </p><p>and today you are reading this that means I have again done something stupid to add one one more reason in that list </p><p>Baby , you have all the rights on me , you can be angry , you can behave rude , you can scold me , you can do anything with me to get your anger out.</p><p>I promise I will be still here only.But please Dont leave. </p><p>I know you , right  now you are angry / frustrated so you are thinking of leaving me but <b>baby please hold a little more </b></p><p>Please dont give up on US , I will do anything to made my deeds right , whatever it takes to get you back</p><p>baby still if you want to leave . I want you to recall the reason <b>'why are you with me till now , why were you trying so hard to be with me even if you have so many reasons to leave?</b>baby for that reason , please let this give one more chance :| </p><p>I know you love me too ,and leaving me is hard for you also , Dont do this with yorself also :( . </p><p> After reading this much if you still wanna leave , you can but remember one thing I am still yours and I am not gonna give up this easily  </p> <p>Still only Yours, </p><p>Heer</p> """



class HtmlWindow(wx.html.HtmlWindow):
    def __init__(self, parent, id, size=(600,400)):
        wx.html.HtmlWindow.__init__(self,parent, id, size=size)
        if "gtk2" in wx.PlatformInfo:
            self.SetStandardFonts()

    def OnLinkClicked(self, link):
        wx.LaunchDefaultBrowser(link.GetHref())

class BreakUpBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "You are Not alone , you got me :)",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1,size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(BreakUPText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()



class LonelyBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "You are Not alone , you got me :)",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1,size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(LonelyText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class RemBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "Just A reminder : How much I love you :) ",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1,size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(ReminderText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class HappyBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "current mood : Happy :)",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1,size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(HappyText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class SadBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "current mood : Sad :( ",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1,size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(SadText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class AboutBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "About <<project>>",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1, size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(aboutText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class NeedLaughBox(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self, None, -1, "Current mood : Need a good laugh ",
            style=wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER|
                wx.TAB_TRAVERSAL)
        hwin = HtmlWindow(self, -1, size=(400,200))
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(laughText % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+25, irep.GetHeight()+10))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()

class Frame(wx.Frame):
    def __init__(self, title):
        wx.Dialog.__init__(self, None, -1, "From heer :)",
            style= wx.DEFAULT_FRAME_STYLE )
        hwin = HtmlWindow(self, -1)
        vers = {}
        vers["python"] = sys.version.split()[0]
        vers["wxpy"] = wx.VERSION_STRING
        hwin.SetPage(guide % vers)
        btn = hwin.FindWindowById(wx.ID_OK)
        irep = hwin.GetInternalRepresentation()
        hwin.SetSize((irep.GetWidth()+100, irep.GetHeight()+100))
        self.SetClientSize(hwin.GetSize())
        self.CentreOnParent(wx.BOTH)
        self.SetFocus()
        self.Bind(wx.EVT_CLOSE, self.OnClose)

        menuBar = wx.MenuBar()


        menu = wx.Menu()


        m_Happy = menu.Append(-1, "&Happy", "Select when you are happy")
        self.Bind(wx.EVT_MENU, self.OnHappy, m_Happy)

        m_Sad = menu.Append(-1, "&Sad", "Select when you are sad ")
        self.Bind(wx.EVT_MENU, self.OnSad, m_Sad)

        m_Rem = menu.Append(-1, "&Reminder", "Open when you need to know how much I love you ")
        self.Bind(wx.EVT_MENU, self.OnRem, m_Rem)

        m_Need = menu.Append(-1, "&Need_A_Laugh ", "Open when you need a good laugh ;)")
        self.Bind(wx.EVT_MENU, self.OnNeedLaugh , m_Need)

        m_Lonely = menu.Append(-1, "&Feeling_Lonely ", "Open when you feel lonely")
        self.Bind(wx.EVT_MENU, self.OnLonely , m_Lonely)

        m_BreakUp = menu.Append(-1, "&Want_Break_Up ", "Open when you don't want to be with me anymore :( ")
        self.Bind(wx.EVT_MENU, self.OnBreakUp , m_BreakUp)

        menuBar.Append(menu, "&Mood")
        menu = wx.Menu()

        m_exit = menu.Append(wx.ID_EXIT, "E&xit\tAlt-X", "Close window and exit program.")
        self.Bind(wx.EVT_MENU, self.OnClose, m_exit)
        m_about = menu.Append(-1, "&About", "Reason for making this :)  ")
        self.Bind(wx.EVT_MENU, self.OnAbout, m_about)
        menuBar.Append(menu, "&File")
        self.SetMenuBar(menuBar)

        self.statusbar = self.CreateStatusBar()

        panel = wx.Panel(self)
        box = wx.BoxSizer(wx.VERTICAL)

        m_text = wx.StaticText(panel, -1, guide )
        m_text.SetFont(wx.Font(14, wx.SWISS, wx.NORMAL, wx.BOLD))
        m_text.SetSize(m_text.GetBestSize())
        box.Add(m_text, 0, wx.ALL, 10)

        m_close = wx.Button(panel, wx.ID_CLOSE, "Close")
        m_close.Bind(wx.EVT_BUTTON, self.OnClose)
        box.Add(m_close, 0, wx.ALL, 10)

        panel.SetSizer(box)
        panel.Layout()

    def OnClose(self, event):
        dlg = wx.MessageDialog(self,
            "Do you really want to close this application?",
            "Confirm Exit", wx.OK|wx.CANCEL|wx.ICON_QUESTION)
        result = dlg.ShowModal()
        dlg.Destroy()
        if result == wx.ID_OK:
            self.Destroy()

    def OnAbout(self, event):
        dlg = AboutBox()
        dlg.ShowModal()
        dlg.Destroy()

    def OnHappy(self, event):
        dlg = HappyBox()
        dlg.ShowModal()
        dlg.Destroy()
    def OnSad(self, event):
        dlg = SadBox()
        dlg.ShowModal()
        dlg.Destroy()
    def OnRem(self, event):
        dlg = RemBox()
        dlg.ShowModal()
        dlg.Destroy()
    def OnNeedLaugh(self, event):
        dlg = NeedLaughBox()
        dlg.ShowModal()
        dlg.Destroy()
    def OnLonely(self, event):
        dlg = LonelyBox()
        dlg.ShowModal()
        dlg.Destroy()
    def OnBreakUp(self, event):
        dlg = BreakUpBox()
        dlg.ShowModal()
        dlg.Destroy()

app = wx.App(redirect=True)   # Error messages go to popup window
top = Frame("<<project>>")
top.Show()
app.MainLoop()
